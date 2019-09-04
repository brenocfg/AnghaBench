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

__attribute__((used)) static bool wm5110_is_rev_d_adsp_memory(unsigned int reg)
{
	if ((reg >= 0x100000 && reg < 0x106000) ||
	    (reg >= 0x180000 && reg < 0x182000) ||
	    (reg >= 0x190000 && reg < 0x198000) ||
	    (reg >= 0x1a8000 && reg < 0x1aa000) ||
	    (reg >= 0x200000 && reg < 0x20f000) ||
	    (reg >= 0x280000 && reg < 0x282000) ||
	    (reg >= 0x290000 && reg < 0x29c000) ||
	    (reg >= 0x2a6000 && reg < 0x2b4000) ||
	    (reg >= 0x300000 && reg < 0x30f000) ||
	    (reg >= 0x380000 && reg < 0x382000) ||
	    (reg >= 0x390000 && reg < 0x3a2000) ||
	    (reg >= 0x3a6000 && reg < 0x3b4000) ||
	    (reg >= 0x400000 && reg < 0x406000) ||
	    (reg >= 0x480000 && reg < 0x482000) ||
	    (reg >= 0x490000 && reg < 0x498000) ||
	    (reg >= 0x4a8000 && reg < 0x4aa000))
		return true;
	else
		return false;
}