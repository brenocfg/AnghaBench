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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pch_gbe_phy_info {int /*<<< orphan*/  addr; } ;
struct pch_gbe_hw {struct pch_gbe_phy_info phy; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PCH_GBE_HAL_MIIM_READ ; 
 scalar_t__ PHY_MAX_REG_ADDRESS ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct pch_gbe_adapter* pch_gbe_hw_to_adapter (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_mac_ctrl_miim (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

s32 pch_gbe_phy_read_reg_miic(struct pch_gbe_hw *hw, u32 offset, u16 *data)
{
	struct pch_gbe_phy_info *phy = &hw->phy;

	if (offset > PHY_MAX_REG_ADDRESS) {
		struct pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);

		netdev_err(adapter->netdev, "PHY Address %d is out of range\n",
			   offset);
		return -EINVAL;
	}
	*data = pch_gbe_mac_ctrl_miim(hw, phy->addr, PCH_GBE_HAL_MIIM_READ,
				      offset, (u16)0);
	return 0;
}