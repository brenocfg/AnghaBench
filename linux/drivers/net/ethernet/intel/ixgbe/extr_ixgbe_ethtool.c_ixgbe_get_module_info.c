#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ (* read_i2c_eeprom ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
struct ethtool_modinfo {int /*<<< orphan*/  eeprom_len; int /*<<< orphan*/  type; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472_LEN ; 
 int IXGBE_SFF_ADDRESSING_MODE ; 
 int IXGBE_SFF_DDM_IMPLEMENTED ; 
 int /*<<< orphan*/  IXGBE_SFF_SFF_8472_COMP ; 
 int /*<<< orphan*/  IXGBE_SFF_SFF_8472_SWAP ; 
 int IXGBE_SFF_SFF_8472_UNSUP ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ixgbe_phy_fw ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ixgbe_get_module_info(struct net_device *dev,
				       struct ethtool_modinfo *modinfo)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct ixgbe_hw *hw = &adapter->hw;
	s32 status;
	u8 sff8472_rev, addr_mode;
	bool page_swap = false;

	if (hw->phy.type == ixgbe_phy_fw)
		return -ENXIO;

	/* Check whether we support SFF-8472 or not */
	status = hw->phy.ops.read_i2c_eeprom(hw,
					     IXGBE_SFF_SFF_8472_COMP,
					     &sff8472_rev);
	if (status)
		return -EIO;

	/* addressing mode is not supported */
	status = hw->phy.ops.read_i2c_eeprom(hw,
					     IXGBE_SFF_SFF_8472_SWAP,
					     &addr_mode);
	if (status)
		return -EIO;

	if (addr_mode & IXGBE_SFF_ADDRESSING_MODE) {
		e_err(drv, "Address change required to access page 0xA2, but not supported. Please report the module type to the driver maintainers.\n");
		page_swap = true;
	}

	if (sff8472_rev == IXGBE_SFF_SFF_8472_UNSUP || page_swap ||
	    !(addr_mode & IXGBE_SFF_DDM_IMPLEMENTED)) {
		/* We have a SFP, but it does not support SFF-8472 */
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	} else {
		/* We have a SFP which supports a revision of SFF-8472. */
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	}

	return 0;
}