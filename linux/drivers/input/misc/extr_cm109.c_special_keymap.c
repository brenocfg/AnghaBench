#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 unsigned short KEY_MICMUTE ; 
 unsigned short KEY_MUTE ; 
 unsigned short KEY_RESERVED ; 
 unsigned short KEY_VOLUMEDOWN ; 
 unsigned short KEY_VOLUMEUP ; 
#define  PLAYBACK_MUTE 131 
#define  RECORD_MUTE 130 
#define  VOLUME_DOWN 129 
#define  VOLUME_UP 128 

__attribute__((used)) static unsigned short special_keymap(int code)
{
	if (code > 0xff) {
		switch (code - 0xff) {
		case RECORD_MUTE:	return KEY_MICMUTE;
		case PLAYBACK_MUTE:	return KEY_MUTE;
		case VOLUME_DOWN:	return KEY_VOLUMEDOWN;
		case VOLUME_UP:		return KEY_VOLUMEUP;
		}
	}
	return KEY_RESERVED;
}