#include <LiquidCrystal_I2C.h>

#define I2C_ADC_ADDR 0x48  //indirizzo modulo adc
#define I2C_LCD_ADDR 0x27  //indirizzo modulo rtc
#define BACKLIGHT_PIN 3  //schermo lcd acceso
#define En_pin 2  //schermo lcd
#define Rw_pin 1  //schermo lcd
#define Rs_pin 0  //schermo lcd
#define D4_pin 4  //schermo lcd
#define D5_pin 5  //schermo lcd
#define D6_pin 6  //schermo lcd
#define D7_pin 7  //schermo lcd

LiquidCrystal_I2C lcd(I2C_LCD_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);  //indirizzo display lcd

char alphabethmin[27]="abcdefghijklmnopqrstuvwxyz";
char alphabethcap[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int numbers[10]={0,1,2,3,4,5,6,7,8,9};

int forward=13;
int up=12;
int down=11;

int val_forward; 
int val_up;
int val_down;

int forwardstate;
int upstate;
int downstate;

int depthlevel=0;
int scroll1=0;
int scroll2=0;
int scroll3=0;
int scroll4=0;
int scroll5=0;

int scroll1max=0;
int scroll2max=0;
int scroll3max=0;
int scroll4max=0;
int scroll5max=0;

int depthlevelvalues[2]={0};
int scroll1values[2]={0};
int scroll2values[2]={0};
int scroll2values[2]={0};
int scroll2values[2]={0};
int scroll2values[2]={0};

int setup=0;

int mod2=0;
int mod8=0;
int mod16=0;

int size2=2;
int size8=8;
int size16=16;

int printed=0;

float averagetemp=20;
unsigned long cstartup=70000;
unsigned long cidle=600000;
unsigned long hstartup=70000;
unsigned long hidle=600000;

float temperature[16]={-2,0,4,8,10,12,14,16,18,20,22,24,26,28,30,32};  //array con valori di temperatura in gradi celsius
unsigned long coldstartup[8]={40000,50000,60000,70000,80000,90000,100000,110000};  //array con valori di tempo di accensione in millisecondi
unsigned long coldidle[8]={480000,540000,600000,660000,720000,780000,840000,900000};  //array con valori di tempo di standby in millisecondi
unsigned long heatstartup[8]={40000,50000,60000,70000,80000,90000,100000,110000};  //array con valori di tempo di accensione in millisecondi
unsigned long heatidle[8]={480000,540000,600000,660000,720000,780000,840000,900000};  //array con valori di tempo di standby in millisecondi

int coldenable[2]={0,1};  //array con valori di force start
int heatenable[2]={0,1};  //array con valori di force start

int colde=1;  //variabile utilizzata per abilitare/disabilitare raffreddamento
int heate=1;  //variabile utilizzata per abilitare/disabilitare riscaldamento

void setup(){
  pinMode(13,INPUT);  //imposta il pin digitale come input
  pinMode(12,INPUT);  //imposta il pin digitale come input
  pinMode(11,INPUT);  //imposta il pin digitale come input
  lcd.begin(16,2);  //inizializza il display
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);  //accendi la luce dell'lcd
  lcd.setBacklight(HIGH);  //accendi la luce dell'lcd
  delay(1000);
}

void loop(){

  /*BUTTONS INPUT READING*/
  val_up=digitalRead(up);
  val_down=digitalRead(down);

  /*MENU NAVIGATION BUTTONS INSTRUCTIONS*/
  if(val_up!=upstate){
    upstate=val_up;
    if(upstate==LOW){
      if(depthlevel==0){
        scroll1++;
      }
      else if(depthlevel==1){
        scroll2++;
      }
      else if(depthlevel==7){
        scroll3++;
      }
      else if(depthlevel==2){
        mod16++;
      }
      else if(depthlevel==3||depthlevel==4||depthlevel==5||depthlevel==6){
        mod8++;
      }
      else if(depthlevel==8||depthlevel==9){
        mod2++;
      }
      printed=0;
    }
  }
  if(val_down!=downstate){
    downstate=val_down;
    if(downstate==LOW){
      if(depthlevel==0){
        scroll1--;
      }
      else if(depthlevel==1){
        scroll2--;
      }
      else if(depthlevel==7){
        scroll3--;
      }
      else if(depthlevel==2){
        mod16--;
      }
      else if(depthlevel==3||depthlevel==4||depthlevel==5||depthlevel==6){
        mod8--;
      }
      else if(depthlevel==8||depthlevel==9){
        mod2--;
      }
      printed=0;
    }
  }
  
  /*MODIFY MENU INTERFACE VISUALIZATION*/
  if(depthlevel==0&&scroll1max==0&&setup==0&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Menu depth      ");
    lcd.setCursor(0,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(depthlevel==0&&scroll1max==0&&setup==1&&printed==0){
    lcd.setCursor(1,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll1max==0&&setup==2&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1 level options ");
    lcd.setCursor(0,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll1max==0&&setup==3&&printed==0){
    lcd.setCursor(1,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll2max==0&&setup==4&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("2 level options ");
    lcd.setCursor(0,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll2max==0&&setup==5&&printed==0){
    lcd.setCursor(1,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll3max==0&&setup==6&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("3 level options ");
    lcd.setCursor(0,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll3max==0&&setup==7&&printed==0){
    lcd.setCursor(1,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll4max==0&&setup==8&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("4 level options ");
    lcd.setCursor(0,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll4max==0&&setup==9&&printed==0){
    lcd.setCursor(1,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll5max==0&&setup==10&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("5 level options ");
    lcd.setCursor(0,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  else if(scroll5max==0&&setup==11&&printed==0){
    lcd.setCursor(1,1);
    lcd.print(numbers[scroll1]);
    printed=1;
  }
  
  /*MODIFY MENU INTERFACE INSTRUCTIONS*/
  if(depthlevel==0&&scroll1max==0&&setup==0){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        depthlevelvalues[0]=numbers[scroll1];
        scroll1=0;
        setup=1;
        printed=0;
      }
    }
  }
  if(depthlevel==0&&scroll1max==0&&setup==1){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        depthlevelvalues[1]=numbers[scroll1];
        for(i=0;i<(size2-1);i++){
          depthlevel=depthlevel+depthlevelvalues[i];
        }
        scroll1=0;
        setup=2;
        printed=0;
      }
    }
  }
  if(scroll1max==0&&setup==2){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll1values[0]=numbers[scroll1];
        scroll1=0;
        setup=3;
        printed=0;
      }
    }
  }
  if(scroll1max==0&&setup==3){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll1values[1]=numbers[scroll1];
        for(i=0;i<(size2-1);i++){
          scroll1max=scroll1max+scroll1values[i];
        }
        scroll1=0;
        setup=4;
        printed=0;
      }
    }
  }
  if(scroll2max==0&&setup==4){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll2values[0]=numbers[scroll1];
        scroll1=0;
        setup=5;
        printed=0;
      }
    }
  }
  if(scroll2max==0&&setup==5){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll2values[1]=numbers[scroll1];
        for(i=0;i<(size2-1);i++){
          scroll2max=scroll2max+scroll2values[i];
        }
        scroll1=0;
        setup=6;
        printed=0;
      }
    }
  }
  if(scroll3max==0&&setup==6){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll3values[0]=numbers[scroll1];
        scroll1=0;
        setup=7;
        printed=0;
      }
    }
  }
  if(scroll3max==0&&setup==7){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll3values[1]=numbers[scroll1];
        for(i=0;i<(size2-1);i++){
          scroll3max=scroll3max+scroll3values[i];
        }
        scroll1=0;
        setup=8;
        printed=0;
      }
    }
  }
  if(scroll4max==0&&setup==8){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll4values[0]=numbers[scroll1];
        scroll1=0;
        setup=9;
        printed=0;
      }
    }
  }
  if(scroll4max==0&&setup==9){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll4values[1]=numbers[scroll1];
        for(i=0;i<(size2-1);i++){
          scroll4max=scroll4max+scroll4values[i];
        }
        scroll1=0;
        setup=10;
        printed=0;
      }
    }
  }
  if(scroll5max==0&&setup==10){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll5values[0]=numbers[scroll1];
        scroll1=0;
        setup=11;
        printed=0;
      }
    }
  }
  if(scroll5max==0&&setup==11){
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        scroll5values[1]=numbers[scroll1];
        for(i=0;i<(size2-1);i++){
          scroll5max=scroll5max+scroll5values[i];
        }
        scroll1=0;
        setup=12;
        printed=0;
      }
    }
  }
  
  /*MENU NAVIGATION VARIABLES RESET*/
  if(setup<12){
    if(scroll1>9||scroll1<0){
      scroll1=0;
    }
  }
  else{
    if(scroll1>scroll1max||scroll1<0){
      scroll1=0;
    }
  }
  if(scroll2>scroll2max||scroll2<0){
      scroll2=0;
  }
  if(scroll3>scroll3max||scroll3<0){
    scroll3=0;
  }
  if(scroll4>scroll4max||scroll4<0){
    scroll4=0;
  }
  if(scroll5>scroll5max||scroll5<0){
    scroll5=0;
  }
  
  /*MAIN MENU*/
  if(depthlevel==0&&scroll1==0&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press forward   ");
    lcd.setCursor(0,1);
    lcd.print("to depthlevel menu   ");
    printed=1;
  }
  if(depthlevel==0&&scroll1==1&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Instant sets    ");
    lcd.setCursor(0,1);
    lcd.print("depthlevel to see    ");
    printed=1;
  }
  if(depthlevel==0&&scroll1==2&&printed==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enable status   ");
    lcd.setCursor(0,1);
    lcd.print("depthlevel to see    ");
    printed=1;
  }
  
  /*ENTERING SUBMENUS INSTRUCTIONS*/
  if(depthlevel==0&&scroll1==1){  //from line 114-121
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        mod2=0;
        mod8=0;
        mod16=0;
        scroll2=0;
        scroll3=0;
        depthlevel=1;
        printed=0;
      }
    }
  }
  if(depthlevel==0&&scroll1==2){  //from line 122-129
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        mod2=0;
        mod8=0;
        mod16=0;
        scroll2=0;
        scroll3=0;
        depthlevel=7;
        printed=0;
      }
    }
  }

  /*SUBMENUS VISUALIZATION*/
  if(depthlevel==1&&scroll1==1&&printed==0){  //from line 132-143
    if(scroll2==0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temperature     ");
      lcd.setCursor(0,1);
      lcd.print(averagetemp);
      printed=1;
    }
    else if(scroll2==1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cold startup    ");
      lcd.setCursor(0,1);
      lcd.print(cstartup);
      printed=1;
    }
    else if(scroll2==2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cold idle       ");
      lcd.setCursor(0,1);
      lcd.print(cidle);
      printed=1;
    }
    else if(scroll2==3){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Heat startup    ");
      lcd.setCursor(0,1);
      lcd.print(hstartup);
      printed=1;
    }
    else if(scroll2==4){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Heat idle       ");
      lcd.setCursor(0,1);
      lcd.print(hidle);
      printed=1;
    }
  }
  else if(depthlevel==7&&scroll1==2&&printed==0){  //from line 145-157  //else to be verified
    if(scroll3==0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cooling status  ");
      lcd.setCursor(0,1);
      lcd.print(colde);
      printed=1;
    }
    else if(scroll3==1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Heating status  ");
      lcd.setCursor(0,1);
      lcd.print(heate);
      printed=1;
    }
  }

  /*ENTERING MODIFY PARAMETERS INSTRUCTIONS*/
  if(depthlevel==1&&scroll1==1&&scroll2==0){  //from line 169-176
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        for(int i=0;i<(size16-1);i++){
          if(temperature[i]==averagetemp){
            mod16=i;
            break;
          }
        }
        mod2=0;
        mod8=0;
        depthlevel=2;
        printed=0;
      }
    }
  }
  if(depthlevel==1&&scroll1==1&&scroll2==1){  //from line 177-184
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        for(int i=0;i<(size8-1);i++){
          if(coldstartup[i]==cstartup){
            mod8=i;
            break;
          }
        }
        mod2=0;
        mod16=0;
        depthlevel=3;
        printed=0;
      }
    }
  }
  if(depthlevel==1&&scroll1==1&&scroll2==2){  //from line 185-192
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        for(int i=0;i<(size8-1);i++){
          if(coldidle[i]==cidle){
            mod8=i;
            break;
          }
        }
        mod2=0;
        mod16=0;
        depthlevel=4;
        printed=0;
      }
    }
  }
  if(depthlevel==1&&scroll1==1&&scroll2==3){  //from line 193-200
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        for(int i=0;i<(size8-1);i++){
          if(heatstartup[i]==hstartup){
            mod8=i;
            break;
          }
        }
        mod2=0;
        mod16=0;
        depthlevel=5;
        printed=0;
      }
    }
  }
  if(depthlevel==1&&scroll1==1&&scroll2==4){  //from line 201-208
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        for(int i=0;i<(size8-1);i++){
          if(heatidle[i]==hidle){
            mod8=i;
            break;
          }
        }
        mod2=0;
        mod16=0;
        depthlevel=6;
        printed=0;
      }
    }
  }
  if(depthlevel==7&&scroll1==2&&scroll3==0){  //from line 211-218
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        for(int i=0;i<(size2-1);i++){
          if(coldenable[i]==colde){
            mod2=i;
            break;
          }
        }
        mod8=0;
        mod16=0;
        depthlevel=8;
        printed=0;
      }
    }
  }
  if(depthlevel==7&&scroll1==2&&scroll3==1){  //from line 219-226
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        for(int i=0;i<(size2-1);i++){
          if(heatenable[i]==heate){
            mod2=i;
            break;
          }
        }
        mod8=0;
        mod16=0;
        depthlevel=9;
        printed=0;
      }
    }
  }

  /*MODIFY PARAMETERS MENUS VISUALIZATION*/
  if(depthlevel==2&&scroll1==1&&scroll2==0&&printed==0){  //from line 252-269
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature     ");
    lcd.setCursor(0,1);
    lcd.print(temperature[mod16]);
    printed==1;
  }
  else if(depthlevel==3&&scroll1==1&&scroll2==1&&printed==0){  //from line 270-287
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cold startup    ");
    lcd.setCursor(0,1);
    lcd.print(coldstartup[mod8]);
    printed==1;
  }
  else if(depthlevel==4&&scroll1==1&&scroll2==2&&printed==0){  //from line 288-305
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cold idle       ");
    lcd.setCursor(0,1);
    lcd.print(coldidle[mod8]);
    printed==1;
  }
  else if(depthlevel==5&&scroll1==1&&scroll2==3&&printed==0){  //from line 306-323
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Heat startup    ");
    lcd.setCursor(0,1);
    lcd.print(heatstartup[mod8]);
    printed==1;
  }
  else if(depthlevel==6&&scroll1==1&&scroll2==4&&printed==0){  //from line 324-341
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Heat idle       ");
    lcd.setCursor(0,1);
    lcd.print(heatidle[mod8]);
    printed==1;
  }
  else if(depthlevel==8&&scroll1==2&&scroll3==0&&printed==0){  //from line 342-359
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cold enable     ");
    lcd.setCursor(0,1);
    lcd.print(coldenable[mod2]);
    printed==1;
  }
  else if(depthlevel==9&&scroll1==2&&scroll3==1&&printed==0){  //from line 360-377
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Heat enable     ");
    lcd.setCursor(0,1);
    lcd.print(heatenable[mod2]);
    printed==1;
  }

  /*MODIFY PARAMETERS INSTRUCTIONS*/
  else if(depthlevel==2){  //from line 387-394
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        averagetemp=temperature[mod16];
        depthlevel=1;
        scroll1=1;
        scroll2=0;
        scroll3=0;
        mod2=0;
        mod8=0;
        mod16=0;
        printed=1;
      }
    }
  }
  else if(depthlevel==3){  //from line 395-402
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        cstartup=coldstartup[mod8];
        depthlevel=1;
        scroll1=1;
        scroll2=1;
        scroll3=0;
        mod2=0;
        mod8=0;
        mod16=0;
        printed=1;
      }
    }
  }
  else if(depthlevel==4){ //from line 403-410
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        cidle=coldidle[mod8];
        depthlevel=1;
        scroll1=1;
        scroll2=2;
        scroll3=0;
        mod2=0;
        mod8=0;
        mod16=0;
        printed=1;
      }
    }
  }
  else if(depthlevel==5){  //from line 411-418
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        hstartup=heatstartup[mod8];
        depthlevel=1;
        scroll1=1;
        scroll2=3;
        scroll3=0;
        mod2=0;
        mod8=0;
        mod16=0;
        printed=1;
      }
    }
  }
  else if(depthlevel==6){  //from line 419-426
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        hidle=heatidle[mod8];
        depthlevel=1;
        scroll1=1;
        scroll2=4;
        scroll3=0;
        mod2=0;
        mod8=0;
        mod16=0;
        printed=1;
      }
    }
  }
  else if(depthlevel==8){  //from line 427-434
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        colde=coldenable[mod2];
        depthlevel=7;
        scroll1=2;
        scroll2=0;
        scroll3=0;
        mod2=0;
        mod8=0;
        mod16=0;
        printed=1;
      }
    }
  }
  else if(depthlevel==9){  //from line 435-442
    val_forward=digitalRead(forward);
    if(val_forward!=forwardstate){
      forwardstate=val_forward;
      if(forwardstate==LOW){
        heate=heatenable[mod2];
        depthlevel=7;
        scroll1=2;
        scroll2=0;
        scroll3=1;
        mod2=0;
        mod8=0;
        mod16=0;
        printed=1;
      }
    }
  }
}
