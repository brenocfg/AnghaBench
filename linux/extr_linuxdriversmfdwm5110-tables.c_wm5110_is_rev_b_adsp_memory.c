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

__attribute__((used)) static bool wm5110_is_rev_b_adsp_memory(unsigned int reg)
{
	if ((reg >= 0x100000 && reg < 0x103000) ||
	    (reg >= 0x180000 && reg < 0x181000) ||
	    (reg >= 0x190000 && reg < 0x192000) ||
	    (reg >= 0x1a8000 && reg < 0x1a9000) ||
	    (reg >= 0x200000 && reg < 0x209000) ||
	    (reg >= 0x280000 && reg < 0x281000) ||
	    (reg >= 0x290000 && reg < 0x29a000) ||
	    (reg >= 0x2a8000 && reg < 0x2aa000) ||
	    (reg >= 0x300000 && reg < 0x30f000) ||
	    (reg >= 0x380000 && reg < 0x382000) ||
	    (reg >= 0x390000 && reg < 0x39e000) ||
	    (reg >= 0x3a8000 && reg < 0x3b6000) ||
	    (reg >= 0x400000 && reg < 0x403000) ||
	    (reg >= 0x480000 && reg < 0x481000) ||
	    (reg >= 0x490000 && reg < 0x492000) ||
	    (reg >= 0x4a8000 && reg < 0x4a9000))
		return true;
	else
		return false;
}