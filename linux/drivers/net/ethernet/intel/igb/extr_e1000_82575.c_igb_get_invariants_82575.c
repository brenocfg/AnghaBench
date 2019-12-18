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
typedef  int u32 ;
struct e1000_mac_info {int type; } ;
struct TYPE_6__ {void* media_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  e100_base_fx; } ;
struct e1000_dev_spec_82575 {int sgmii_active; int module_plugged; TYPE_2__ eth_flags; } ;
struct TYPE_4__ {struct e1000_dev_spec_82575 _82575; } ;
struct e1000_hw {int device_id; struct e1000_mac_info mac; TYPE_3__ phy; TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
#define  E1000_CTRL_EXT_LINK_MODE_1000BASE_KX 169 
 int E1000_CTRL_EXT_LINK_MODE_MASK ; 
#define  E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES 168 
#define  E1000_CTRL_EXT_LINK_MODE_SGMII 167 
#define  E1000_DEV_ID_82575EB_COPPER 166 
#define  E1000_DEV_ID_82575EB_FIBER_SERDES 165 
#define  E1000_DEV_ID_82575GB_QUAD_COPPER 164 
#define  E1000_DEV_ID_82576 163 
#define  E1000_DEV_ID_82576_FIBER 162 
#define  E1000_DEV_ID_82576_NS 161 
#define  E1000_DEV_ID_82576_NS_SERDES 160 
#define  E1000_DEV_ID_82576_QUAD_COPPER 159 
#define  E1000_DEV_ID_82576_QUAD_COPPER_ET2 158 
#define  E1000_DEV_ID_82576_SERDES 157 
#define  E1000_DEV_ID_82576_SERDES_QUAD 156 
#define  E1000_DEV_ID_82580_COPPER 155 
#define  E1000_DEV_ID_82580_COPPER_DUAL 154 
#define  E1000_DEV_ID_82580_FIBER 153 
#define  E1000_DEV_ID_82580_QUAD_FIBER 152 
#define  E1000_DEV_ID_82580_SERDES 151 
#define  E1000_DEV_ID_82580_SGMII 150 
#define  E1000_DEV_ID_DH89XXCC_BACKPLANE 149 
#define  E1000_DEV_ID_DH89XXCC_SERDES 148 
#define  E1000_DEV_ID_DH89XXCC_SFP 147 
#define  E1000_DEV_ID_DH89XXCC_SGMII 146 
#define  E1000_DEV_ID_I210_COPPER 145 
#define  E1000_DEV_ID_I210_COPPER_FLASHLESS 144 
#define  E1000_DEV_ID_I210_FIBER 143 
#define  E1000_DEV_ID_I210_SERDES 142 
#define  E1000_DEV_ID_I210_SERDES_FLASHLESS 141 
#define  E1000_DEV_ID_I210_SGMII 140 
#define  E1000_DEV_ID_I211_COPPER 139 
#define  E1000_DEV_ID_I350_COPPER 138 
#define  E1000_DEV_ID_I350_FIBER 137 
#define  E1000_DEV_ID_I350_SERDES 136 
#define  E1000_DEV_ID_I350_SGMII 135 
#define  E1000_DEV_ID_I354_BACKPLANE_1GBPS 134 
#define  E1000_DEV_ID_I354_BACKPLANE_2_5GBPS 133 
#define  E1000_DEV_ID_I354_SGMII 132 
 scalar_t__ E1000_ERR_MAC_INIT ; 
 int e1000_82575 ; 
#define  e1000_82576 131 
 int e1000_82580 ; 
#define  e1000_i210 130 
#define  e1000_i211 129 
#define  e1000_i350 128 
 int e1000_i354 ; 
 void* e1000_media_type_copper ; 
 void* e1000_media_type_internal_serdes ; 
 void* e1000_media_type_unknown ; 
 scalar_t__ igb_init_mac_params_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_init_mbx_params_pf (struct e1000_hw*) ; 
 scalar_t__ igb_init_nvm_params_82575 (struct e1000_hw*) ; 
 scalar_t__ igb_init_nvm_params_i210 (struct e1000_hw*) ; 
 scalar_t__ igb_init_phy_params_82575 (struct e1000_hw*) ; 
 scalar_t__ igb_set_sfp_media_type_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_sgmii_uses_mdio_82575 (struct e1000_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_get_invariants_82575(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	s32 ret_val;
	u32 ctrl_ext = 0;
	u32 link_mode = 0;

	switch (hw->device_id) {
	case E1000_DEV_ID_82575EB_COPPER:
	case E1000_DEV_ID_82575EB_FIBER_SERDES:
	case E1000_DEV_ID_82575GB_QUAD_COPPER:
		mac->type = e1000_82575;
		break;
	case E1000_DEV_ID_82576:
	case E1000_DEV_ID_82576_NS:
	case E1000_DEV_ID_82576_NS_SERDES:
	case E1000_DEV_ID_82576_FIBER:
	case E1000_DEV_ID_82576_SERDES:
	case E1000_DEV_ID_82576_QUAD_COPPER:
	case E1000_DEV_ID_82576_QUAD_COPPER_ET2:
	case E1000_DEV_ID_82576_SERDES_QUAD:
		mac->type = e1000_82576;
		break;
	case E1000_DEV_ID_82580_COPPER:
	case E1000_DEV_ID_82580_FIBER:
	case E1000_DEV_ID_82580_QUAD_FIBER:
	case E1000_DEV_ID_82580_SERDES:
	case E1000_DEV_ID_82580_SGMII:
	case E1000_DEV_ID_82580_COPPER_DUAL:
	case E1000_DEV_ID_DH89XXCC_SGMII:
	case E1000_DEV_ID_DH89XXCC_SERDES:
	case E1000_DEV_ID_DH89XXCC_BACKPLANE:
	case E1000_DEV_ID_DH89XXCC_SFP:
		mac->type = e1000_82580;
		break;
	case E1000_DEV_ID_I350_COPPER:
	case E1000_DEV_ID_I350_FIBER:
	case E1000_DEV_ID_I350_SERDES:
	case E1000_DEV_ID_I350_SGMII:
		mac->type = e1000_i350;
		break;
	case E1000_DEV_ID_I210_COPPER:
	case E1000_DEV_ID_I210_FIBER:
	case E1000_DEV_ID_I210_SERDES:
	case E1000_DEV_ID_I210_SGMII:
	case E1000_DEV_ID_I210_COPPER_FLASHLESS:
	case E1000_DEV_ID_I210_SERDES_FLASHLESS:
		mac->type = e1000_i210;
		break;
	case E1000_DEV_ID_I211_COPPER:
		mac->type = e1000_i211;
		break;
	case E1000_DEV_ID_I354_BACKPLANE_1GBPS:
	case E1000_DEV_ID_I354_SGMII:
	case E1000_DEV_ID_I354_BACKPLANE_2_5GBPS:
		mac->type = e1000_i354;
		break;
	default:
		return -E1000_ERR_MAC_INIT;
	}

	/* Set media type */
	/* The 82575 uses bits 22:23 for link mode. The mode can be changed
	 * based on the EEPROM. We cannot rely upon device ID. There
	 * is no distinguishable difference between fiber and internal
	 * SerDes mode on the 82575. There can be an external PHY attached
	 * on the SGMII interface. For this, we'll set sgmii_active to true.
	 */
	hw->phy.media_type = e1000_media_type_copper;
	dev_spec->sgmii_active = false;
	dev_spec->module_plugged = false;

	ctrl_ext = rd32(E1000_CTRL_EXT);

	link_mode = ctrl_ext & E1000_CTRL_EXT_LINK_MODE_MASK;
	switch (link_mode) {
	case E1000_CTRL_EXT_LINK_MODE_1000BASE_KX:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		break;
	case E1000_CTRL_EXT_LINK_MODE_SGMII:
		/* Get phy control interface type set (MDIO vs. I2C)*/
		if (igb_sgmii_uses_mdio_82575(hw)) {
			hw->phy.media_type = e1000_media_type_copper;
			dev_spec->sgmii_active = true;
			break;
		}
		/* fall through - for I2C based SGMII */
	case E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES:
		/* read media type from SFP EEPROM */
		ret_val = igb_set_sfp_media_type_82575(hw);
		if ((ret_val != 0) ||
		    (hw->phy.media_type == e1000_media_type_unknown)) {
			/* If media type was not identified then return media
			 * type defined by the CTRL_EXT settings.
			 */
			hw->phy.media_type = e1000_media_type_internal_serdes;

			if (link_mode == E1000_CTRL_EXT_LINK_MODE_SGMII) {
				hw->phy.media_type = e1000_media_type_copper;
				dev_spec->sgmii_active = true;
			}

			break;
		}

		/* do not change link mode for 100BaseFX */
		if (dev_spec->eth_flags.e100_base_fx)
			break;

		/* change current link mode setting */
		ctrl_ext &= ~E1000_CTRL_EXT_LINK_MODE_MASK;

		if (hw->phy.media_type == e1000_media_type_copper)
			ctrl_ext |= E1000_CTRL_EXT_LINK_MODE_SGMII;
		else
			ctrl_ext |= E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;

		wr32(E1000_CTRL_EXT, ctrl_ext);

		break;
	default:
		break;
	}

	/* mac initialization and operations */
	ret_val = igb_init_mac_params_82575(hw);
	if (ret_val)
		goto out;

	/* NVM initialization */
	ret_val = igb_init_nvm_params_82575(hw);
	switch (hw->mac.type) {
	case e1000_i210:
	case e1000_i211:
		ret_val = igb_init_nvm_params_i210(hw);
		break;
	default:
		break;
	}

	if (ret_val)
		goto out;

	/* if part supports SR-IOV then initialize mailbox parameters */
	switch (mac->type) {
	case e1000_82576:
	case e1000_i350:
		igb_init_mbx_params_pf(hw);
		break;
	default:
		break;
	}

	/* setup PHY parameters */
	ret_val = igb_init_phy_params_82575(hw);

out:
	return ret_val;
}