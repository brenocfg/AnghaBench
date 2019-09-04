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
struct omap_hwmod {int dummy; } ;
struct clockdomain {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int _clkdm_clk_hwmod_enable (struct clockdomain*) ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 

int clkdm_hwmod_enable(struct clockdomain *clkdm, struct omap_hwmod *oh)
{
	/* The clkdm attribute does not exist yet prior OMAP4 */
	if (cpu_is_omap24xx() || cpu_is_omap34xx())
		return 0;

	/*
	 * XXX Rewrite this code to maintain a list of enabled
	 * downstream hwmods for debugging purposes?
	 */

	if (!oh)
		return -EINVAL;

	return _clkdm_clk_hwmod_enable(clkdm);
}