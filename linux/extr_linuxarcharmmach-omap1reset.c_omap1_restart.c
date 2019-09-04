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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_RSTCT1 ; 
 int /*<<< orphan*/  DPLL_CTL ; 
 scalar_t__ cpu_is_omap5912 () ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int,int /*<<< orphan*/ ) ; 

void omap1_restart(enum reboot_mode mode, const char *cmd)
{
	/*
	 * Workaround for 5912/1611b bug mentioned in sprz209d.pdf p. 28
	 * "Global Software Reset Affects Traffic Controller Frequency".
	 */
	if (cpu_is_omap5912()) {
		omap_writew(omap_readw(DPLL_CTL) & ~(1 << 4), DPLL_CTL);
		omap_writew(0x8, ARM_RSTCT1);
	}

	omap_writew(1, ARM_RSTCT1);
}