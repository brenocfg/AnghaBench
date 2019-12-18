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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 ir_xbof_change(u8 xbof)
{
	u8 result;

	/* reference irda-usb.c */
	switch (xbof) {
	case 48:
		result = 0x10;
		break;
	case 28:
	case 24:
		result = 0x20;
		break;
	default:
	case 12:
		result = 0x30;
		break;
	case  5:
	case  6:
		result = 0x40;
		break;
	case  3:
		result = 0x50;
		break;
	case  2:
		result = 0x60;
		break;
	case  1:
		result = 0x70;
		break;
	case  0:
		result = 0x80;
		break;
	}

	return(result);
}