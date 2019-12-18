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
 unsigned long DEBUG_LEVEL_1 ; 
 unsigned long DEBUG_LEVEL_2 ; 
 unsigned long DEBUG_LEVEL_3 ; 
 unsigned long DEBUG_LEVEL_4 ; 
 unsigned long DEBUG_LEVEL_5 ; 
 unsigned long DEBUG_LEVEL_6 ; 

void fbtft_expand_debug_value(unsigned long *debug)
{
	switch (*debug & 0x7) {
	case 1:
		*debug |= DEBUG_LEVEL_1;
		break;
	case 2:
		*debug |= DEBUG_LEVEL_2;
		break;
	case 3:
		*debug |= DEBUG_LEVEL_3;
		break;
	case 4:
		*debug |= DEBUG_LEVEL_4;
		break;
	case 5:
		*debug |= DEBUG_LEVEL_5;
		break;
	case 6:
		*debug |= DEBUG_LEVEL_6;
		break;
	case 7:
		*debug = 0xFFFFFFFF;
		break;
	}
}