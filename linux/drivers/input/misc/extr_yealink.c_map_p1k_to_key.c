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
 int EINVAL ; 
 int KEY_0 ; 
 int KEY_1 ; 
 int KEY_2 ; 
 int KEY_3 ; 
 int KEY_4 ; 
 int KEY_5 ; 
 int KEY_6 ; 
 int KEY_7 ; 
 int KEY_8 ; 
 int KEY_9 ; 
 int KEY_BACKSPACE ; 
 int KEY_DOWN ; 
 int KEY_ENTER ; 
 int KEY_ESC ; 
 int KEY_KPASTERISK ; 
 int KEY_LEFT ; 
 int KEY_LEFTSHIFT ; 
 int KEY_RIGHT ; 
 int KEY_UP ; 

__attribute__((used)) static int map_p1k_to_key(int scancode)
{
	switch(scancode) {		/* phone key:	*/
	case 0x23: return KEY_LEFT;	/*   IN		*/
	case 0x33: return KEY_UP;	/*   up		*/
	case 0x04: return KEY_RIGHT;	/*   OUT	*/
	case 0x24: return KEY_DOWN;	/*   down	*/
	case 0x03: return KEY_ENTER;	/*   pickup	*/
	case 0x14: return KEY_BACKSPACE; /*  C		*/
	case 0x13: return KEY_ESC;	/*   hangup	*/
	case 0x00: return KEY_1;	/*   1		*/
	case 0x01: return KEY_2;	/*   2 		*/
	case 0x02: return KEY_3;	/*   3		*/
	case 0x10: return KEY_4;	/*   4		*/
	case 0x11: return KEY_5;	/*   5		*/
	case 0x12: return KEY_6;	/*   6		*/
	case 0x20: return KEY_7;	/*   7		*/
	case 0x21: return KEY_8;	/*   8		*/
	case 0x22: return KEY_9;	/*   9		*/
	case 0x30: return KEY_KPASTERISK; /* *		*/
	case 0x31: return KEY_0;	/*   0		*/
	case 0x32: return KEY_LEFTSHIFT |
			  KEY_3 << 8;	/*   #		*/
	}
	return -EINVAL;
}