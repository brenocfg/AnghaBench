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
struct TYPE_2__ {scalar_t__ ssc_ctrl_reg; int /*<<< orphan*/  ssc_ctrl_en_mask; scalar_t__ defaults_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  pll_readl (scalar_t__,struct tegra_clk_pll*) ; 
 int /*<<< orphan*/  pll_writel (int /*<<< orphan*/ ,scalar_t__,struct tegra_clk_pll*) ; 

__attribute__((used)) static void pll_clk_start_ss(struct tegra_clk_pll *pll)
{
	if (pll->params->defaults_set && pll->params->ssc_ctrl_reg) {
		u32 val = pll_readl(pll->params->ssc_ctrl_reg, pll);

		val |= pll->params->ssc_ctrl_en_mask;
		pll_writel(val, pll->params->ssc_ctrl_reg, pll);
	}
}