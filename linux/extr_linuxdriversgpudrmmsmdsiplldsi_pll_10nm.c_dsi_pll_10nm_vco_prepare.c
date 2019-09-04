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
struct dsi_pll_10nm {scalar_t__ phy_cmn_mmio; struct dsi_pll_10nm* slave; int /*<<< orphan*/  id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_DSI_10nm_PHY_CMN_PLL_CNTRL ; 
 scalar_t__ REG_DSI_10nm_PHY_CMN_RBUF_CTRL ; 
 int dsi_pll_10nm_lock_status (struct dsi_pll_10nm*) ; 
 int /*<<< orphan*/  dsi_pll_enable_global_clk (struct dsi_pll_10nm*) ; 
 int /*<<< orphan*/  dsi_pll_enable_pll_bias (struct dsi_pll_10nm*) ; 
 struct msm_dsi_pll* hw_clk_to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  pll_write (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct dsi_pll_10nm* to_pll_10nm (struct msm_dsi_pll*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int dsi_pll_10nm_vco_prepare(struct clk_hw *hw)
{
	struct msm_dsi_pll *pll = hw_clk_to_pll(hw);
	struct dsi_pll_10nm *pll_10nm = to_pll_10nm(pll);
	int rc;

	dsi_pll_enable_pll_bias(pll_10nm);
	if (pll_10nm->slave)
		dsi_pll_enable_pll_bias(pll_10nm->slave);

	/* Start PLL */
	pll_write(pll_10nm->phy_cmn_mmio + REG_DSI_10nm_PHY_CMN_PLL_CNTRL,
		  0x01);

	/*
	 * ensure all PLL configurations are written prior to checking
	 * for PLL lock.
	 */
	wmb();

	/* Check for PLL lock */
	rc = dsi_pll_10nm_lock_status(pll_10nm);
	if (rc) {
		pr_err("PLL(%d) lock failed\n", pll_10nm->id);
		goto error;
	}

	pll->pll_on = true;

	dsi_pll_enable_global_clk(pll_10nm);
	if (pll_10nm->slave)
		dsi_pll_enable_global_clk(pll_10nm->slave);

	pll_write(pll_10nm->phy_cmn_mmio + REG_DSI_10nm_PHY_CMN_RBUF_CTRL,
		  0x01);
	if (pll_10nm->slave)
		pll_write(pll_10nm->slave->phy_cmn_mmio +
			  REG_DSI_10nm_PHY_CMN_RBUF_CTRL, 0x01);

error:
	return rc;
}