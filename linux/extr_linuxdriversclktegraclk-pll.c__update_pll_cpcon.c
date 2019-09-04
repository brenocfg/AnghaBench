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
typedef  int u32 ;
struct tegra_clk_pll_freq_table {int cpcon; scalar_t__ n; } ;
struct tegra_clk_pll {TYPE_1__* params; } ;
struct TYPE_2__ {int flags; int vco_max; } ;

/* Variables and functions */
 scalar_t__ PLLDU_LFCON_SET_DIVN ; 
 int PLL_MISC_CPCON_MASK ; 
 int PLL_MISC_CPCON_SHIFT ; 
 int PLL_MISC_DCCON_SHIFT ; 
 int PLL_MISC_LFCON_MASK ; 
 int PLL_MISC_LFCON_SHIFT ; 
 int TEGRA_PLL_SET_DCCON ; 
 int TEGRA_PLL_SET_LFCON ; 
 int pll_readl_misc (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel_misc (int,struct tegra_clk_pll*) ; 

__attribute__((used)) static void _update_pll_cpcon(struct tegra_clk_pll *pll,
			      struct tegra_clk_pll_freq_table *cfg,
			      unsigned long rate)
{
	u32 val;

	val = pll_readl_misc(pll);

	val &= ~(PLL_MISC_CPCON_MASK << PLL_MISC_CPCON_SHIFT);
	val |= cfg->cpcon << PLL_MISC_CPCON_SHIFT;

	if (pll->params->flags & TEGRA_PLL_SET_LFCON) {
		val &= ~(PLL_MISC_LFCON_MASK << PLL_MISC_LFCON_SHIFT);
		if (cfg->n >= PLLDU_LFCON_SET_DIVN)
			val |= 1 << PLL_MISC_LFCON_SHIFT;
	} else if (pll->params->flags & TEGRA_PLL_SET_DCCON) {
		val &= ~(1 << PLL_MISC_DCCON_SHIFT);
		if (rate >= (pll->params->vco_max >> 1))
			val |= 1 << PLL_MISC_DCCON_SHIFT;
	}

	pll_writel_misc(val, pll);
}