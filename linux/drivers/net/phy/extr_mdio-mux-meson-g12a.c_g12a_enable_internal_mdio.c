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
struct g12a_mdio_mux {int pll_is_enabled; scalar_t__ regs; int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int EPHY_DFLT_ADD ; 
 int EPHY_G12A_ID ; 
 int EPHY_MODE_RMII ; 
 scalar_t__ ETH_PHY_CNTL0 ; 
 scalar_t__ ETH_PHY_CNTL1 ; 
 scalar_t__ ETH_PHY_CNTL2 ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int PHY_CNTL1_CLKFREQ ; 
 int PHY_CNTL1_CLK_EN ; 
 int /*<<< orphan*/  PHY_CNTL1_MII_MODE ; 
 int PHY_CNTL1_PHY_ENB ; 
 int /*<<< orphan*/  PHY_CNTL1_ST_MODE ; 
 int /*<<< orphan*/  PHY_CNTL1_ST_PHYADD ; 
 int PHY_CNTL2_RX_CLK_EPHY ; 
 int PHY_CNTL2_SMI_SRC_MAC ; 
 int PHY_CNTL2_USE_INTERNAL ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int g12a_enable_internal_mdio(struct g12a_mdio_mux *priv)
{
	int ret;

	/* Enable the phy clock */
	if (!priv->pll_is_enabled) {
		ret = clk_prepare_enable(priv->pll);
		if (ret)
			return ret;
	}

	priv->pll_is_enabled = true;

	/* Initialize ephy control */
	writel(EPHY_G12A_ID, priv->regs + ETH_PHY_CNTL0);
	writel(FIELD_PREP(PHY_CNTL1_ST_MODE, 3) |
	       FIELD_PREP(PHY_CNTL1_ST_PHYADD, EPHY_DFLT_ADD) |
	       FIELD_PREP(PHY_CNTL1_MII_MODE, EPHY_MODE_RMII) |
	       PHY_CNTL1_CLK_EN |
	       PHY_CNTL1_CLKFREQ |
	       PHY_CNTL1_PHY_ENB,
	       priv->regs + ETH_PHY_CNTL1);
	writel(PHY_CNTL2_USE_INTERNAL |
	       PHY_CNTL2_SMI_SRC_MAC |
	       PHY_CNTL2_RX_CLK_EPHY,
	       priv->regs + ETH_PHY_CNTL2);

	return 0;
}