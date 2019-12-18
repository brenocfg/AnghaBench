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
 unsigned int LCD_WINCTRL1_FRM ; 
#define  LCD_WINCTRL1_FRM_12BPP 141 
#define  LCD_WINCTRL1_FRM_16BPP556 140 
#define  LCD_WINCTRL1_FRM_16BPP565 139 
#define  LCD_WINCTRL1_FRM_16BPP655 138 
#define  LCD_WINCTRL1_FRM_16BPPA1555 137 
#define  LCD_WINCTRL1_FRM_16BPPA5551 136 
#define  LCD_WINCTRL1_FRM_16BPPI1555 135 
#define  LCD_WINCTRL1_FRM_16BPPI5551 134 
#define  LCD_WINCTRL1_FRM_1BPP 133 
#define  LCD_WINCTRL1_FRM_24BPP 132 
#define  LCD_WINCTRL1_FRM_2BPP 131 
#define  LCD_WINCTRL1_FRM_32BPP 130 
#define  LCD_WINCTRL1_FRM_4BPP 129 
#define  LCD_WINCTRL1_FRM_8BPP 128 

__attribute__((used)) static int winbpp (unsigned int winctrl1)
{
	int bits = 0;

	/* how many bits are needed for each pixel format */
	switch (winctrl1 & LCD_WINCTRL1_FRM) {
	case LCD_WINCTRL1_FRM_1BPP:
		bits = 1;
		break;
	case LCD_WINCTRL1_FRM_2BPP:
		bits = 2;
		break;
	case LCD_WINCTRL1_FRM_4BPP:
		bits = 4;
		break;
	case LCD_WINCTRL1_FRM_8BPP:
		bits = 8;
		break;
	case LCD_WINCTRL1_FRM_12BPP:
	case LCD_WINCTRL1_FRM_16BPP655:
	case LCD_WINCTRL1_FRM_16BPP565:
	case LCD_WINCTRL1_FRM_16BPP556:
	case LCD_WINCTRL1_FRM_16BPPI1555:
	case LCD_WINCTRL1_FRM_16BPPI5551:
	case LCD_WINCTRL1_FRM_16BPPA1555:
	case LCD_WINCTRL1_FRM_16BPPA5551:
		bits = 16;
		break;
	case LCD_WINCTRL1_FRM_24BPP:
	case LCD_WINCTRL1_FRM_32BPP:
		bits = 32;
		break;
	}

	return bits;
}