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
 unsigned short KEY_DOWN ; 
 unsigned short KEY_ENTER ; 
 unsigned short KEY_ESC ; 
 unsigned short KEY_NUMERIC_0 ; 
 unsigned short KEY_NUMERIC_1 ; 
 unsigned short KEY_NUMERIC_2 ; 
 unsigned short KEY_NUMERIC_3 ; 
 unsigned short KEY_NUMERIC_4 ; 
 unsigned short KEY_NUMERIC_5 ; 
 unsigned short KEY_NUMERIC_6 ; 
 unsigned short KEY_NUMERIC_7 ; 
 unsigned short KEY_NUMERIC_8 ; 
 unsigned short KEY_NUMERIC_9 ; 
 unsigned short KEY_NUMERIC_POUND ; 
 unsigned short KEY_NUMERIC_STAR ; 
 unsigned short KEY_UP ; 
 unsigned short special_keymap (int) ; 

__attribute__((used)) static unsigned short keymap_gtalk(int scancode)
{
	switch (scancode) {
	case 0x11: return KEY_NUMERIC_0;
	case 0x21: return KEY_NUMERIC_1;
	case 0x41: return KEY_NUMERIC_2;
	case 0x81: return KEY_NUMERIC_3;
	case 0x12: return KEY_NUMERIC_4;
	case 0x22: return KEY_NUMERIC_5;
	case 0x42: return KEY_NUMERIC_6;
	case 0x82: return KEY_NUMERIC_7;
	case 0x14: return KEY_NUMERIC_8;
	case 0x24: return KEY_NUMERIC_9;
	case 0x44: return KEY_NUMERIC_POUND;	/* # */
	case 0x84: return KEY_NUMERIC_STAR;	/* * */
	case 0x18: return KEY_ENTER;		/* Talk (green handset) */
	case 0x28: return KEY_ESC;		/* End (red handset) */
	case 0x48: return KEY_UP;		/* Menu up (rocker switch) */
	case 0x88: return KEY_DOWN;		/* Menu down (rocker switch) */
	default:   return special_keymap(scancode);
	}
}