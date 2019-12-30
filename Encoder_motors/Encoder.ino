#define inter_pin 2
#define Enc_A 3
#define pwm 10
#define dir 12

long encoder = 0;

int interval = 1000;
int previousmillis = 0;
int currentmillis= 0;

int rpm=0;
boolean measureRpm = false;
int mot_pwm =0;

void setup()
{
  Serial.begin(9600);

  pinMode(inter_pin,INPUT);
  pinMode(Enc_A ,INPUT);
  pinMode(pwm,OUTPUT);
  pinMode(dir,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(Enc_A), change , RISING);

  Serial.println("\n\n");
  Serial.println("Measuring RPM");
  
}

void loop()
{
  if(digitalRead(inter_pin) == LOW)
  {
  measureRpm = !measureRpm;
  if(measureRpm == true)
  {
    Serial.println("start");
  }

  else if(measureRpm==false)
  {
    Serial.println("sTOP");
    
  }

  delay(400);
  encoder=0;
  previousmillis = millis();
  
}

currentmillis = millis();
if(currentmillis - previousmillis > interval)
{
  previousmillis = currentmillis;

  if(measureRpm ==true && mot_pwm<250)
  {
    mot_pwm +=50;
    analogWrite(pwm , mot_pwm);
  }
  else if(measureRpm == false && mot_pwm>0)
  {
    mot_pwm -=50;
    analogWrite(pwm, mot_pwm);
   
  }

  rpm =(float)(encoder *60 / 120);

  if(mot_pwm>0 || rpm >0)
  {
    Serial.println(mot_pwm);
    Serial.println('\t');
    Serial.println(encoder);
    Serial.println("pulse /");
    Serial.println(rpm);
    Serial.println("RPM");
  }
  encoder=0;
}
}
void change()
{
  encoder++;
}

}
  
