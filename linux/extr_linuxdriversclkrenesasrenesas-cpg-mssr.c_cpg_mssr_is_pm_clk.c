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
struct of_phandle_args {scalar_t__ np; int args_count; int* args; } ;
struct cpg_mssr_clk_domain {scalar_t__ np; unsigned int num_core_pm_clks; int* core_pm_clks; } ;

/* Variables and functions */
#define  CPG_CORE 129 
#define  CPG_MOD 128 

__attribute__((used)) static bool cpg_mssr_is_pm_clk(const struct of_phandle_args *clkspec,
			       struct cpg_mssr_clk_domain *pd)
{
	unsigned int i;

	if (clkspec->np != pd->np || clkspec->args_count != 2)
		return false;

	switch (clkspec->args[0]) {
	case CPG_CORE:
		for (i = 0; i < pd->num_core_pm_clks; i++)
			if (clkspec->args[1] == pd->core_pm_clks[i])
				return true;
		return false;

	case CPG_MOD:
		return true;

	default:
		return false;
	}
}