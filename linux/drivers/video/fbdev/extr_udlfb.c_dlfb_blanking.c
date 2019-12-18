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
#define  FB_BLANK_HSYNC_SUSPEND 131 
#define  FB_BLANK_NORMAL 130 
#define  FB_BLANK_POWERDOWN 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 char* dlfb_set_register (char*,int,int) ; 

__attribute__((used)) static char *dlfb_blanking(char *buf, int fb_blank)
{
	u8 reg;

	switch (fb_blank) {
	case FB_BLANK_POWERDOWN:
		reg = 0x07;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		reg = 0x05;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		reg = 0x03;
		break;
	case FB_BLANK_NORMAL:
		reg = 0x01;
		break;
	default:
		reg = 0x00;
	}

	buf = dlfb_set_register(buf, 0x1F, reg);

	return buf;
}