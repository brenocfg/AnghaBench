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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct tegra_clk_pll_freq_table {int m; unsigned long n; int /*<<< orphan*/  p; } ;
struct tegra_clk_pll {TYPE_1__* params; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int flags; unsigned long fixed_rate; int /*<<< orphan*/  (* set_gain ) (struct tegra_clk_pll_freq_table*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int PLL_BASE_BYPASS ; 
 int PLL_BASE_OVERRIDE ; 
 int TEGRA_PLLM ; 
 int TEGRA_PLLMB ; 
 int TEGRA_PLL_BYPASS ; 
 int TEGRA_PLL_FIXED ; 
 int TEGRA_PLL_VCO_OUT ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_pll_mnp (struct tegra_clk_pll*,struct tegra_clk_pll_freq_table*) ; 
 scalar_t__ _get_table_rate (struct clk_hw*,struct tegra_clk_pll_freq_table*,unsigned long,unsigned long) ; 
 int _hw_to_p_div (struct clk_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 int pll_readl_base (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tegra_clk_pll_freq_table*) ; 
 struct tegra_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pll_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct tegra_clk_pll *pll = to_clk_pll(hw);
	struct tegra_clk_pll_freq_table cfg;
	u32 val;
	u64 rate = parent_rate;
	int pdiv;

	val = pll_readl_base(pll);

	if ((pll->params->flags & TEGRA_PLL_BYPASS) && (val & PLL_BASE_BYPASS))
		return parent_rate;

	if ((pll->params->flags & TEGRA_PLL_FIXED) &&
	    !(pll->params->flags & (TEGRA_PLLM | TEGRA_PLLMB)) &&
			!(val & PLL_BASE_OVERRIDE)) {
		struct tegra_clk_pll_freq_table sel;
		if (_get_table_rate(hw, &sel, pll->params->fixed_rate,
					parent_rate)) {
			pr_err("Clock %s has unknown fixed frequency\n",
			       clk_hw_get_name(hw));
			BUG();
		}
		return pll->params->fixed_rate;
	}

	_get_pll_mnp(pll, &cfg);

	if (pll->params->flags & TEGRA_PLL_VCO_OUT) {
		pdiv = 1;
	} else {
		pdiv = _hw_to_p_div(hw, cfg.p);
		if (pdiv < 0) {
			WARN(1, "Clock %s has invalid pdiv value : 0x%x\n",
			     clk_hw_get_name(hw), cfg.p);
			pdiv = 1;
		}
	}

	if (pll->params->set_gain)
		pll->params->set_gain(&cfg);

	cfg.m *= pdiv;

	rate *= cfg.n;
	do_div(rate, cfg.m);

	return rate;
}