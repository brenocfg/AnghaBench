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
 int /*<<< orphan*/  OMAP2XXX_DPLL_AUTOIDLE_LOW_POWER_STOP ; 
 int /*<<< orphan*/  _omap2xxx_set_dpll_autoidle (int /*<<< orphan*/ ) ; 

void omap2xxx_cm_set_dpll_disable_autoidle(void)
{
	_omap2xxx_set_dpll_autoidle(OMAP2XXX_DPLL_AUTOIDLE_LOW_POWER_STOP);
}