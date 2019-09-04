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
struct TYPE_3__ {scalar_t__ (* read_i2c_sff8472 ) (struct ixgbe_hw*,int,int*) ;scalar_t__ (* read_i2c_eeprom ) (struct ixgbe_hw*,int,int*) ;} ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  state; struct ixgbe_hw hw; } ;
struct ethtool_eeprom {int len; int offset; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int ETH_MODULE_SFF_8079_LEN ; 
 scalar_t__ IXGBE_ERR_PHY_ADDR_INVALID ; 
 int /*<<< orphan*/  __IXGBE_IN_SFP_INIT ; 
 scalar_t__ ixgbe_phy_fw ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_get_module_eeprom(struct net_device *dev,
					 struct ethtool_eeprom *ee,
					 u8 *data)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct ixgbe_hw *hw = &adapter->hw;
	s32 status = IXGBE_ERR_PHY_ADDR_INVALID;
	u8 databyte = 0xFF;
	int i = 0;

	if (ee->len == 0)
		return -EINVAL;

	if (hw->phy.type == ixgbe_phy_fw)
		return -ENXIO;

	for (i = ee->offset; i < ee->offset + ee->len; i++) {
		/* I2C reads can take long time */
		if (test_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
			return -EBUSY;

		if (i < ETH_MODULE_SFF_8079_LEN)
			status = hw->phy.ops.read_i2c_eeprom(hw, i, &databyte);
		else
			status = hw->phy.ops.read_i2c_sff8472(hw, i, &databyte);

		if (status)
			return -EIO;

		data[i - ee->offset] = databyte;
	}

	return 0;
}