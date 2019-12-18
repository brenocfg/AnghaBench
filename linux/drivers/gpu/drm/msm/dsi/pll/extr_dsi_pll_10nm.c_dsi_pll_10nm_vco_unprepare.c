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
struct msm_dsi_pll {int pll_on; } ;
struct dsi_pll_10nm {struct dsi_pll_10nm* slave; scalar_t__ phy_cmn_mmio; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_DSI_10nm_PHY_CMN_PLL_CNTRL ; 
 int /*<<< orphan*/  dsi_pll_disable_global_clk (struct dsi_pll_10nm*) ; 
 int /*<<< orphan*/  dsi_pll_disable_sub (struct dsi_pll_10nm*) ; 
 struct msm_dsi_pll* hw_clk_to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  pll_write (scalar_t__,int /*<<< orphan*/ ) ; 
 struct dsi_pll_10nm* to_pll_10nm (struct msm_dsi_pll*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dsi_pll_10nm_vco_unprepare(struct clk_hw *hw)
{
	struct msm_dsi_pll *pll = hw_clk_to_pll(hw);
	struct dsi_pll_10nm *pll_10nm = to_pll_10nm(pll);

	/*
	 * To avoid any stray glitches while abruptly powering down the PLL
	 * make sure to gate the clock using the clock enable bit before
	 * powering down the PLL
	 */
	dsi_pll_disable_global_clk(pll_10nm);
	pll_write(pll_10nm->phy_cmn_mmio + REG_DSI_10nm_PHY_CMN_PLL_CNTRL, 0);
	dsi_pll_disable_sub(pll_10nm);
	if (pll_10nm->slave) {
		dsi_pll_disable_global_clk(pll_10nm->slave);
		dsi_pll_disable_sub(pll_10nm->slave);
	}
	/* flush, ensure all register writes are done */
	wmb();
	pll->pll_on = false;
}