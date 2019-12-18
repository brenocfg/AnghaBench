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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int id; } ;
struct pch_gbe_hw {TYPE_1__ phy; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHY_AR8031_DBG_DAT ; 
 int /*<<< orphan*/  PHY_AR8031_DBG_OFF ; 
 int /*<<< orphan*/  PHY_AR8031_SERDES ; 
 int /*<<< orphan*/  PHY_AR8031_SERDES_TX_CLK_DLY ; 
#define  PHY_AR803X_ID 128 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct pch_gbe_adapter* pch_gbe_hw_to_adapter (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_read_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pch_gbe_phy_write_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pch_gbe_phy_tx_clk_delay(struct pch_gbe_hw *hw)
{
	/* The RGMII interface requires a ~2ns TX clock delay. This is typically
	 * done in layout with a longer trace or via PHY strapping, but can also
	 * be done via PHY configuration registers.
	 */
	struct pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u16 mii_reg;
	int ret = 0;

	switch (hw->phy.id) {
	case PHY_AR803X_ID:
		netdev_dbg(adapter->netdev,
			   "Configuring AR803X PHY for 2ns TX clock delay\n");
		pch_gbe_phy_read_reg_miic(hw, PHY_AR8031_DBG_OFF, &mii_reg);
		ret = pch_gbe_phy_write_reg_miic(hw, PHY_AR8031_DBG_OFF,
						 PHY_AR8031_SERDES);
		if (ret)
			break;

		pch_gbe_phy_read_reg_miic(hw, PHY_AR8031_DBG_DAT, &mii_reg);
		mii_reg |= PHY_AR8031_SERDES_TX_CLK_DLY;
		ret = pch_gbe_phy_write_reg_miic(hw, PHY_AR8031_DBG_DAT,
						 mii_reg);
		break;
	default:
		netdev_err(adapter->netdev,
			   "Unknown PHY (%x), could not set TX clock delay\n",
			   hw->phy.id);
		return -EINVAL;
	}

	if (ret)
		netdev_err(adapter->netdev,
			   "Could not configure tx clock delay for PHY\n");
	return ret;
}