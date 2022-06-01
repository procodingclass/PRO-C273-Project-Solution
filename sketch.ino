#include <SD.h>
#include <RTClib.h>

RTC_DS1307 rtc;

File file;

String names[20];
String dates[20];
String current_date = "";

void setup() {
  Serial.begin(9600);
  SD.begin();
  rtc.begin();

  file = SD.open("birthday.txt", FILE_READ);

  read_current_date();
  read_file();

  match_date();

}

void read_file() {
  String paragraph;
  int i = 0;

  if (file) {
    while (file.available()) {
      String data = file.readStringUntil(':');
      names[i] = data;
      String data1 = file.readStringUntil('\n');
      dates[i] = data1;
      i++;
    }
  }
}

void read_current_date() {

  DateTime now = rtc.now();
  current_date = "";

  if (now.day() < 10) {
    current_date.concat("0");
  }
  current_date.concat(now.day());
  current_date.concat("-");
  if (now.month() < 10) {
    current_date.concat("0");
  }
  current_date.concat(now.month());

}

void match_date() {
  int found=0;
  for (int i = 0; i < 20; i++) {
    int flag = 0;
    for (int j = 0; j < 5; j++) {
      if (current_date[j] == dates[i][j]) {
        flag++;
      }
    }
    if (flag == 5) {
      Serial.print("Happy Birthday, ");
      Serial.println(names[i]);
      delay(3000);
      found=1;
    }
  }
  
  if(found==0){
    Serial.println("No birthday");
    Serial.println("today!!");
    delay(5000);
  }

}

void loop() {

}