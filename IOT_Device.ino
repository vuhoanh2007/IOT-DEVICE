#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <DNSServer.h>  
#include <FirebaseESP8266.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"

#define FIREBASE_HOST  "iot-devices-c0515-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "N1DJL1wfwIhogIxPlNb5FQUN39hdkC8d4TGCfNak"
FirebaseData fbdo;

const int relay1 = 16;
const int relay2 = 5;
const int relay3 = 4;
const int relay4 = 0;

int ival, ival2, ival3, ival4;

String timee;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "vn.pool.ntp.org", 25200, 60000);


void configModeCallback (WiFiManager *myWiFiManager)
{
  Serial.println("Che do cai dat");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup(){
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  if (!wifiManager.autoConnect())
  {
    Serial.println("Ket noi that bai");
    ESP.reset();
    delay(1000);
  }
  Serial.println("Da ket noi...");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  timeClient.begin();
  
}

void loop()
{
  timeClient.update();
  timee = timeClient.getFormattedTime().substring(0,timeClient.getFormattedTime().length()-3);
  Firebase.set(fbdo,"Time", String(timee));
  if (Firebase.get(fbdo, "/D1")) {
    ival = fbdo.to<int>();
    if (ival == 0){
      digitalWrite(relay1, HIGH);
      }else{
        digitalWrite(relay1, LOW);
        }
    }
  if (Firebase.get(fbdo, "/D2")) {
    ival2 = fbdo.to<int>();
    if (ival2 == 0){
      digitalWrite(relay2, HIGH);
      }else{
        digitalWrite(relay2, LOW);
        }
    }
  if (Firebase.get(fbdo, "/D3")) {
    ival3 = fbdo.to<int>();
    if (ival3 == 0){
      digitalWrite(relay3, HIGH);
      }else{
        digitalWrite(relay3, LOW);
        }
    }
  if (Firebase.get(fbdo, "/D4")) {
    ival4 = fbdo.to<int>();
    if (ival4 == 0){
      digitalWrite(relay4, HIGH);
      }else{
        digitalWrite(relay4, LOW);
        }
    }
}
