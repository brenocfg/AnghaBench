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
typedef  int u32 ;
struct ti_pipe3 {int /*<<< orphan*/  pll_ctrl_base; } ;
struct pipe3_dpll_params {int n; int freq; int m; int mf; int sd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PLL_CONFIGURATION1 ; 
 int /*<<< orphan*/  PLL_CONFIGURATION2 ; 
 int /*<<< orphan*/  PLL_CONFIGURATION3 ; 
 int /*<<< orphan*/  PLL_CONFIGURATION4 ; 
 int /*<<< orphan*/  PLL_GO ; 
 int PLL_REGM_F_MASK ; 
 int PLL_REGM_F_SHIFT ; 
 int PLL_REGM_MASK ; 
 int PLL_REGM_SHIFT ; 
 int PLL_REGN_MASK ; 
 int PLL_REGN_SHIFT ; 
 int PLL_SD_MASK ; 
 int PLL_SD_SHIFT ; 
 int PLL_SELFREQDCO_MASK ; 
 int PLL_SELFREQDCO_SHIFT ; 
 int SET_PLL_GO ; 
 int ti_pipe3_dpll_wait_lock (struct ti_pipe3*) ; 
 struct pipe3_dpll_params* ti_pipe3_get_dpll_params (struct ti_pipe3*) ; 
 int ti_pipe3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pipe3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ti_pipe3_dpll_program(struct ti_pipe3 *phy)
{
	u32			val;
	struct pipe3_dpll_params *dpll_params;

	dpll_params = ti_pipe3_get_dpll_params(phy);
	if (!dpll_params)
		return -EINVAL;

	val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_CONFIGURATION1);
	val &= ~PLL_REGN_MASK;
	val |= dpll_params->n << PLL_REGN_SHIFT;
	ti_pipe3_writel(phy->pll_ctrl_base, PLL_CONFIGURATION1, val);

	val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_CONFIGURATION2);
	val &= ~PLL_SELFREQDCO_MASK;
	val |= dpll_params->freq << PLL_SELFREQDCO_SHIFT;
	ti_pipe3_writel(phy->pll_ctrl_base, PLL_CONFIGURATION2, val);

	val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_CONFIGURATION1);
	val &= ~PLL_REGM_MASK;
	val |= dpll_params->m << PLL_REGM_SHIFT;
	ti_pipe3_writel(phy->pll_ctrl_base, PLL_CONFIGURATION1, val);

	val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_CONFIGURATION4);
	val &= ~PLL_REGM_F_MASK;
	val |= dpll_params->mf << PLL_REGM_F_SHIFT;
	ti_pipe3_writel(phy->pll_ctrl_base, PLL_CONFIGURATION4, val);

	val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_CONFIGURATION3);
	val &= ~PLL_SD_MASK;
	val |= dpll_params->sd << PLL_SD_SHIFT;
	ti_pipe3_writel(phy->pll_ctrl_base, PLL_CONFIGURATION3, val);

	ti_pipe3_writel(phy->pll_ctrl_base, PLL_GO, SET_PLL_GO);

	return ti_pipe3_dpll_wait_lock(phy);
}