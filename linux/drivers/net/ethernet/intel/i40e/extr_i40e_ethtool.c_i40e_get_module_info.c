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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct i40e_vsi {int /*<<< orphan*/  netdev; struct i40e_pf* back; } ;
struct TYPE_3__ {scalar_t__ phy_type; int* module_type; } ;
struct TYPE_4__ {TYPE_1__ link_info; } ;
struct i40e_hw {int flags; TYPE_2__ phy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct ethtool_modinfo {void* eeprom_len; void* type; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 void* ETH_MODULE_SFF_8079 ; 
 void* ETH_MODULE_SFF_8079_LEN ; 
 void* ETH_MODULE_SFF_8436 ; 
 void* ETH_MODULE_SFF_8472 ; 
 void* ETH_MODULE_SFF_8472_LEN ; 
 void* ETH_MODULE_SFF_8636 ; 
 int /*<<< orphan*/  I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE ; 
 int I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE ; 
 int /*<<< orphan*/  I40E_I2C_EEPROM_DEV_ADDR ; 
 void* I40E_MODULE_QSFP_MAX_LEN ; 
 int /*<<< orphan*/  I40E_MODULE_REVISION_ADDR ; 
 int /*<<< orphan*/  I40E_MODULE_SFF_8472_COMP ; 
 int /*<<< orphan*/  I40E_MODULE_SFF_8472_SWAP ; 
 int I40E_MODULE_SFF_ADDR_MODE ; 
 int I40E_MODULE_SFF_DDM_IMPLEMENTED ; 
#define  I40E_MODULE_TYPE_QSFP28 130 
#define  I40E_MODULE_TYPE_QSFP_PLUS 129 
#define  I40E_MODULE_TYPE_SFP 128 
 scalar_t__ I40E_PHY_TYPE_EMPTY ; 
 scalar_t__ i40e_aq_get_phy_register (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_update_link_info (struct i40e_hw*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int i40e_get_module_info(struct net_device *netdev,
				struct ethtool_modinfo *modinfo)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	u32 sff8472_comp = 0;
	u32 sff8472_swap = 0;
	u32 sff8636_rev = 0;
	i40e_status status;
	u32 type = 0;

	/* Check if firmware supports reading module EEPROM. */
	if (!(hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE)) {
		netdev_err(vsi->netdev, "Module EEPROM memory read not supported. Please update the NVM image.\n");
		return -EINVAL;
	}

	status = i40e_update_link_info(hw);
	if (status)
		return -EIO;

	if (hw->phy.link_info.phy_type == I40E_PHY_TYPE_EMPTY) {
		netdev_err(vsi->netdev, "Cannot read module EEPROM memory. No module connected.\n");
		return -EINVAL;
	}

	type = hw->phy.link_info.module_type[0];

	switch (type) {
	case I40E_MODULE_TYPE_SFP:
		status = i40e_aq_get_phy_register(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				I40E_I2C_EEPROM_DEV_ADDR,
				I40E_MODULE_SFF_8472_COMP,
				&sff8472_comp, NULL);
		if (status)
			return -EIO;

		status = i40e_aq_get_phy_register(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				I40E_I2C_EEPROM_DEV_ADDR,
				I40E_MODULE_SFF_8472_SWAP,
				&sff8472_swap, NULL);
		if (status)
			return -EIO;

		/* Check if the module requires address swap to access
		 * the other EEPROM memory page.
		 */
		if (sff8472_swap & I40E_MODULE_SFF_ADDR_MODE) {
			netdev_warn(vsi->netdev, "Module address swap to access page 0xA2 is not supported.\n");
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		} else if (sff8472_comp == 0x00) {
			/* Module is not SFF-8472 compliant */
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		} else if (!(sff8472_swap & I40E_MODULE_SFF_DDM_IMPLEMENTED)) {
			/* Module is SFF-8472 compliant but doesn't implement
			 * Digital Diagnostic Monitoring (DDM).
			 */
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		} else {
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		}
		break;
	case I40E_MODULE_TYPE_QSFP_PLUS:
		/* Read from memory page 0. */
		status = i40e_aq_get_phy_register(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				0,
				I40E_MODULE_REVISION_ADDR,
				&sff8636_rev, NULL);
		if (status)
			return -EIO;
		/* Determine revision compliance byte */
		if (sff8636_rev > 0x02) {
			/* Module is SFF-8636 compliant */
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = I40E_MODULE_QSFP_MAX_LEN;
		} else {
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = I40E_MODULE_QSFP_MAX_LEN;
		}
		break;
	case I40E_MODULE_TYPE_QSFP28:
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = I40E_MODULE_QSFP_MAX_LEN;
		break;
	default:
		netdev_err(vsi->netdev, "Module type unrecognized\n");
		return -EINVAL;
	}
	return 0;
}