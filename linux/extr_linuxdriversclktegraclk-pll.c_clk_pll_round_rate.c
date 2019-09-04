#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_clk_pll_freq_table {long output_rate; } ;
struct tegra_clk_pll {TYPE_1__* params; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int flags; long fixed_rate; scalar_t__ (* calc_rate ) (struct clk_hw*,struct tegra_clk_pll_freq_table*,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 long EINVAL ; 
 int TEGRA_PLLM ; 
 int TEGRA_PLLMB ; 
 int TEGRA_PLL_FIXED ; 
 scalar_t__ _get_table_rate (struct clk_hw*,struct tegra_clk_pll_freq_table*,unsigned long,unsigned long) ; 
 long clk_hw_get_rate (struct clk_hw*) ; 
 scalar_t__ stub1 (struct clk_hw*,struct tegra_clk_pll_freq_table*,unsigned long,unsigned long) ; 
 struct tegra_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static long clk_pll_round_rate(struct clk_hw *hw, unsigned long rate,
			unsigned long *prate)
{
	struct tegra_clk_pll *pll = to_clk_pll(hw);
	struct tegra_clk_pll_freq_table cfg;

	if (pll->params->flags & TEGRA_PLL_FIXED) {
		/* PLLM/MB are used for memory; we do not change rate */
		if (pll->params->flags & (TEGRA_PLLM | TEGRA_PLLMB))
			return clk_hw_get_rate(hw);
		return pll->params->fixed_rate;
	}

	if (_get_table_rate(hw, &cfg, rate, *prate) &&
	    pll->params->calc_rate(hw, &cfg, rate, *prate))
		return -EINVAL;

	return cfg.output_rate;
}