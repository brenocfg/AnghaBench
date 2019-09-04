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
typedef  long long u32 ;

/* Variables and functions */
 long long CORE_CLK_SRC_32K ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dpll_core_ck ; 
 long long omap2_get_dpll_rate (int /*<<< orphan*/ ) ; 
 long long omap2xxx_cm_get_core_clk_src () ; 

unsigned long omap2xxx_clk_get_core_rate(void)
{
	long long core_clk;
	u32 v;

	WARN_ON(!dpll_core_ck);

	core_clk = omap2_get_dpll_rate(dpll_core_ck);

	v = omap2xxx_cm_get_core_clk_src();

	if (v == CORE_CLK_SRC_32K)
		core_clk = 32768;
	else
		core_clk *= v;

	return core_clk;
}