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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_clk_pll {TYPE_1__* params; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  lock_enable_bit_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int TEGRA_PLL_HAS_LOCK_ENABLE ; 
 int TEGRA_PLL_USE_LOCK ; 
 int /*<<< orphan*/  pll_readl_misc (struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel_misc (int /*<<< orphan*/ ,struct tegra_clk_pll*) ; 

__attribute__((used)) static void clk_pll_enable_lock(struct tegra_clk_pll *pll)
{
	u32 val;

	if (!(pll->params->flags & TEGRA_PLL_USE_LOCK))
		return;

	if (!(pll->params->flags & TEGRA_PLL_HAS_LOCK_ENABLE))
		return;

	val = pll_readl_misc(pll);
	val |= BIT(pll->params->lock_enable_bit_idx);
	pll_writel_misc(val, pll);
}