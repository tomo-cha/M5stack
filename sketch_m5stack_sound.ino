#include <M5Stack.h>
#include <WiFi.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

// 音源
AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

void setup() {
  M5.begin();
  M5.Speaker.begin();
  WiFi.mode(WIFI_OFF);
  M5.Lcd.setTextSize(3);
  M5.Speaker.setVolume(7);
}

void loop() {
  M5.update();
  if(M5.BtnA.wasPressed()) {　
    M5.Speaker.tone(659, 200);
    delay(200);
    M5.Speaker.tone(523, 200);
  }
  if(M5.BtnB.wasPressed()) {
    playMP3("/sendSonic2.mp3");
  }
  if(M5.BtnC.wasPressed()) {
    M5.Speaker.tone(440, 100);
    delay(100);
    M5.Speaker.mute();
    delay(100);
    M5.Speaker.tone(440, 100);
    delay(100);
    M5.Speaker.mute();
    delay(100);
    M5.Speaker.tone(440, 100);
  }
}

void playMP3(char *filename) {
  file = new AudioFileSourceSD(filename);
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 1); // Output to builtInDAC
  out->SetOutputModeMono(true);
  out->SetGain(1.0);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  while (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  }
}
