#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  link_duplex; int /*<<< orphan*/  link_speed; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg_advertised; } ;
struct pch_gbe_hw {TYPE_2__ mac; TYPE_1__ phy; } ;
struct pch_gbe_adapter {TYPE_3__* pdata; int /*<<< orphan*/  netdev; int /*<<< orphan*/  mii; } ;
struct ethtool_cmd {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {scalar_t__ phy_tx_clk_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PHYSP_CTRL_ASSERT_CRS_TX ; 
 int /*<<< orphan*/  PHY_PHYSP_CONTROL ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int /*<<< orphan*/ ) ; 
 int mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 int mii_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct pch_gbe_adapter* pch_gbe_hw_to_adapter (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_read_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_gbe_phy_sw_reset (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_tx_clk_delay (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_write_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pch_gbe_phy_init_setting(struct pch_gbe_hw *hw)
{
	struct pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	struct ethtool_cmd     cmd = { .cmd = ETHTOOL_GSET };
	int ret;
	u16 mii_reg;

	ret = mii_ethtool_gset(&adapter->mii, &cmd);
	if (ret)
		netdev_err(adapter->netdev, "Error: mii_ethtool_gset\n");

	ethtool_cmd_speed_set(&cmd, hw->mac.link_speed);
	cmd.duplex = hw->mac.link_duplex;
	cmd.advertising = hw->phy.autoneg_advertised;
	cmd.autoneg = hw->mac.autoneg;
	pch_gbe_phy_write_reg_miic(hw, MII_BMCR, BMCR_RESET);
	ret = mii_ethtool_sset(&adapter->mii, &cmd);
	if (ret)
		netdev_err(adapter->netdev, "Error: mii_ethtool_sset\n");

	pch_gbe_phy_sw_reset(hw);

	pch_gbe_phy_read_reg_miic(hw, PHY_PHYSP_CONTROL, &mii_reg);
	mii_reg |= PHYSP_CTRL_ASSERT_CRS_TX;
	pch_gbe_phy_write_reg_miic(hw, PHY_PHYSP_CONTROL, mii_reg);

	/* Setup a TX clock delay on certain platforms */
	if (adapter->pdata && adapter->pdata->phy_tx_clk_delay)
		pch_gbe_phy_tx_clk_delay(hw);
}