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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;
struct igb_adapter {struct e1000_hw hw; } ;
struct ethtool_modinfo {int /*<<< orphan*/  eeprom_len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472_LEN ; 
 int /*<<< orphan*/  IGB_SFF_8472_COMP ; 
 int /*<<< orphan*/  IGB_SFF_8472_SWAP ; 
 int IGB_SFF_8472_UNSUP ; 
 int IGB_SFF_ADDRESSING_MODE ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_unknown ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igb_read_phy_reg_i2c (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_get_module_info(struct net_device *netdev,
			       struct ethtool_modinfo *modinfo)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 status = 0;
	u16 sff8472_rev, addr_mode;
	bool page_swap = false;

	if ((hw->phy.media_type == e1000_media_type_copper) ||
	    (hw->phy.media_type == e1000_media_type_unknown))
		return -EOPNOTSUPP;

	/* Check whether we support SFF-8472 or not */
	status = igb_read_phy_reg_i2c(hw, IGB_SFF_8472_COMP, &sff8472_rev);
	if (status)
		return -EIO;

	/* addressing mode is not supported */
	status = igb_read_phy_reg_i2c(hw, IGB_SFF_8472_SWAP, &addr_mode);
	if (status)
		return -EIO;

	/* addressing mode is not supported */
	if ((addr_mode & 0xFF) & IGB_SFF_ADDRESSING_MODE) {
		hw_dbg("Address change required to access page 0xA2, but not supported. Please report the module type to the driver maintainers.\n");
		page_swap = true;
	}

	if ((sff8472_rev & 0xFF) == IGB_SFF_8472_UNSUP || page_swap) {
		/* We have an SFP, but it does not support SFF-8472 */
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	} else {
		/* We have an SFP which supports a revision of SFF-8472 */
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	}

	return 0;
}