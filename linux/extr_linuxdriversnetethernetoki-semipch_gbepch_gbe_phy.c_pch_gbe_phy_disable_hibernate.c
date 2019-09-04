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
 int /*<<< orphan*/  PHY_AR8031_HIBERNATE ; 
 int /*<<< orphan*/  PHY_AR8031_PS_HIB_EN ; 
#define  PHY_AR803X_ID 128 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct pch_gbe_adapter* pch_gbe_hw_to_adapter (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_read_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pch_gbe_phy_write_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pch_gbe_phy_disable_hibernate(struct pch_gbe_hw *hw)
{
	struct pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u16 mii_reg;
	int ret = 0;

	switch (hw->phy.id) {
	case PHY_AR803X_ID:
		netdev_dbg(adapter->netdev,
			   "Disabling hibernation for AR803X PHY\n");
		ret = pch_gbe_phy_write_reg_miic(hw, PHY_AR8031_DBG_OFF,
						 PHY_AR8031_HIBERNATE);
		if (ret)
			break;

		pch_gbe_phy_read_reg_miic(hw, PHY_AR8031_DBG_DAT, &mii_reg);
		mii_reg &= ~PHY_AR8031_PS_HIB_EN;
		ret = pch_gbe_phy_write_reg_miic(hw, PHY_AR8031_DBG_DAT,
						 mii_reg);
		break;
	default:
		netdev_err(adapter->netdev,
			   "Unknown PHY (%x), could not disable hibernation\n",
			   hw->phy.id);
		return -EINVAL;
	}

	if (ret)
		netdev_err(adapter->netdev,
			   "Could not disable PHY hibernation\n");
	return ret;
}