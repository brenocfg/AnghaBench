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
struct clk_hw {int dummy; } ;
struct tegra_bpmp_clk {unsigned int id; struct clk_hw hw; } ;
struct tegra_bpmp {unsigned int num_clocks; struct tegra_bpmp_clk** clocks; } ;
struct of_phandle_args {unsigned int* args; } ;

/* Variables and functions */

__attribute__((used)) static struct clk_hw *tegra_bpmp_clk_of_xlate(struct of_phandle_args *clkspec,
					      void *data)
{
	unsigned int id = clkspec->args[0], i;
	struct tegra_bpmp *bpmp = data;

	for (i = 0; i < bpmp->num_clocks; i++) {
		struct tegra_bpmp_clk *clk = bpmp->clocks[i];

		if (!clk)
			continue;

		if (clk->id == id)
			return &clk->hw;
	}

	return NULL;
}