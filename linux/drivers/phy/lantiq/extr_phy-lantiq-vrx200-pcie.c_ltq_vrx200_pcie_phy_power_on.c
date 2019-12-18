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
struct phy {int dummy; } ;
struct ltq_vrx200_pcie_phy_priv {int /*<<< orphan*/  pdi_clk; int /*<<< orphan*/  phy_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_vrx200_pcie_phy_apply_workarounds (struct phy*) ; 
 int /*<<< orphan*/  ltq_vrx200_pcie_phy_common_setup (struct phy*) ; 
 scalar_t__ ltq_vrx200_pcie_phy_wait_for_pll (struct phy*) ; 
 int /*<<< orphan*/  pcie_phy_36mhz_mode_setup (struct phy*) ; 
 struct ltq_vrx200_pcie_phy_priv* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int ltq_vrx200_pcie_phy_power_on(struct phy *phy)
{
	struct ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	int ret;

	/* Enable PDI to access PCIe PHY register */
	ret = clk_prepare_enable(priv->pdi_clk);
	if (ret)
		goto err;

	/* Configure PLL and PHY clock */
	ltq_vrx200_pcie_phy_common_setup(phy);

	pcie_phy_36mhz_mode_setup(phy);

	/* Enable the PCIe PHY and make PLL setting take effect */
	ret = clk_prepare_enable(priv->phy_clk);
	if (ret)
		goto err_disable_pdi_clk;

	/* Check if we are in "startup ready" status */
	if (ltq_vrx200_pcie_phy_wait_for_pll(phy) != 0)
		goto err_disable_phy_clk;

	ltq_vrx200_pcie_phy_apply_workarounds(phy);

	return 0;

err_disable_phy_clk:
	clk_disable_unprepare(priv->phy_clk);
err_disable_pdi_clk:
	clk_disable_unprepare(priv->pdi_clk);
err:
	return ret;
}