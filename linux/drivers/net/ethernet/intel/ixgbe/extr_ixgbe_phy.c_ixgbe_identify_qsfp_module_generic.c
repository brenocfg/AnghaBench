#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_9__ {scalar_t__ (* read_i2c_eeprom ) (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_10__ {int sfp_type; scalar_t__ type; int sfp_setup_needed; int multispeed_fiber; scalar_t__ id; TYPE_4__ ops; } ;
struct TYPE_6__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* get_device_caps ) (struct ixgbe_hw*,int*) ;int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct TYPE_7__ {TYPE_1__ ops; } ;
struct TYPE_8__ {scalar_t__ lan_id; } ;
struct ixgbe_hw {TYPE_5__ phy; scalar_t__ allow_unsupported_sfp; TYPE_2__ mac; TYPE_3__ bus; struct ixgbe_adapter* back; } ;
struct ixgbe_adapter {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum ixgbe_sfp_type { ____Placeholder_ixgbe_sfp_type } ixgbe_sfp_type ;

/* Variables and functions */
 int IXGBE_DEVICE_CAPS_ALLOW_ANY_SFP ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_PRESENT ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 scalar_t__ IXGBE_SFF_10GBASELR_CAPABLE ; 
 scalar_t__ IXGBE_SFF_10GBASESR_CAPABLE ; 
 scalar_t__ IXGBE_SFF_1GBASELX_CAPABLE ; 
 scalar_t__ IXGBE_SFF_1GBASESX_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_IDENTIFIER ; 
 scalar_t__ IXGBE_SFF_IDENTIFIER_QSFP_PLUS ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_10GBE_COMP ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_1GBE_COMP ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_CABLE_LENGTH ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_CONNECTOR ; 
 scalar_t__ IXGBE_SFF_QSFP_CONNECTOR_NOT_SEPARABLE ; 
 scalar_t__ IXGBE_SFF_QSFP_DA_ACTIVE_CABLE ; 
 scalar_t__ IXGBE_SFF_QSFP_DA_PASSIVE_CABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_DEVICE_TECH ; 
 scalar_t__ IXGBE_SFF_QSFP_TRANSMITER_850NM_VCSEL ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_VENDOR_OUI_BYTE0 ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_VENDOR_OUI_BYTE1 ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_VENDOR_OUI_BYTE2 ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_BYTE0_SHIFT ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_BYTE1_SHIFT ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_BYTE2_SHIFT ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_INTEL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_media_type_fiber_qsfp ; 
 scalar_t__ ixgbe_phy_qsfp_active_unknown ; 
 scalar_t__ ixgbe_phy_qsfp_intel ; 
 scalar_t__ ixgbe_phy_qsfp_passive_unknown ; 
 scalar_t__ ixgbe_phy_qsfp_unknown ; 
 void* ixgbe_phy_sfp_unsupported ; 
 scalar_t__ ixgbe_phy_unknown ; 
 int ixgbe_sfp_type_da_act_lmt_core0 ; 
 int ixgbe_sfp_type_da_act_lmt_core1 ; 
 int ixgbe_sfp_type_da_cu_core0 ; 
 int ixgbe_sfp_type_da_cu_core1 ; 
 void* ixgbe_sfp_type_not_present ; 
 int ixgbe_sfp_type_srlr_core0 ; 
 int ixgbe_sfp_type_srlr_core1 ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub10 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub11 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub12 (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub9 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static s32 ixgbe_identify_qsfp_module_generic(struct ixgbe_hw *hw)
{
	struct ixgbe_adapter *adapter = hw->back;
	s32 status;
	u32 vendor_oui = 0;
	enum ixgbe_sfp_type stored_sfp_type = hw->phy.sfp_type;
	u8 identifier = 0;
	u8 comp_codes_1g = 0;
	u8 comp_codes_10g = 0;
	u8 oui_bytes[3] = {0, 0, 0};
	u16 enforce_sfp = 0;
	u8 connector = 0;
	u8 cable_length = 0;
	u8 device_tech = 0;
	bool active_cable = false;

	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_fiber_qsfp) {
		hw->phy.sfp_type = ixgbe_sfp_type_not_present;
		return IXGBE_ERR_SFP_NOT_PRESENT;
	}

	/* LAN ID is needed for sfp_type determination */
	hw->mac.ops.set_lan_id(hw);

	status = hw->phy.ops.read_i2c_eeprom(hw, IXGBE_SFF_IDENTIFIER,
					     &identifier);

	if (status != 0)
		goto err_read_i2c_eeprom;

	if (identifier != IXGBE_SFF_IDENTIFIER_QSFP_PLUS) {
		hw->phy.type = ixgbe_phy_sfp_unsupported;
		return IXGBE_ERR_SFP_NOT_SUPPORTED;
	}

	hw->phy.id = identifier;

	status = hw->phy.ops.read_i2c_eeprom(hw, IXGBE_SFF_QSFP_10GBE_COMP,
					     &comp_codes_10g);

	if (status != 0)
		goto err_read_i2c_eeprom;

	status = hw->phy.ops.read_i2c_eeprom(hw, IXGBE_SFF_QSFP_1GBE_COMP,
					     &comp_codes_1g);

	if (status != 0)
		goto err_read_i2c_eeprom;

	if (comp_codes_10g & IXGBE_SFF_QSFP_DA_PASSIVE_CABLE) {
		hw->phy.type = ixgbe_phy_qsfp_passive_unknown;
		if (hw->bus.lan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_core0;
		else
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_core1;
	} else if (comp_codes_10g & (IXGBE_SFF_10GBASESR_CAPABLE |
				     IXGBE_SFF_10GBASELR_CAPABLE)) {
		if (hw->bus.lan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_srlr_core0;
		else
			hw->phy.sfp_type = ixgbe_sfp_type_srlr_core1;
	} else {
		if (comp_codes_10g & IXGBE_SFF_QSFP_DA_ACTIVE_CABLE)
			active_cable = true;

		if (!active_cable) {
			/* check for active DA cables that pre-date
			 * SFF-8436 v3.6
			 */
			hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_CONNECTOR,
					&connector);

			hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_CABLE_LENGTH,
					&cable_length);

			hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_DEVICE_TECH,
					&device_tech);

			if ((connector ==
				     IXGBE_SFF_QSFP_CONNECTOR_NOT_SEPARABLE) &&
			    (cable_length > 0) &&
			    ((device_tech >> 4) ==
				     IXGBE_SFF_QSFP_TRANSMITER_850NM_VCSEL))
				active_cable = true;
		}

		if (active_cable) {
			hw->phy.type = ixgbe_phy_qsfp_active_unknown;
			if (hw->bus.lan_id == 0)
				hw->phy.sfp_type =
						ixgbe_sfp_type_da_act_lmt_core0;
			else
				hw->phy.sfp_type =
						ixgbe_sfp_type_da_act_lmt_core1;
		} else {
			/* unsupported module type */
			hw->phy.type = ixgbe_phy_sfp_unsupported;
			return IXGBE_ERR_SFP_NOT_SUPPORTED;
		}
	}

	if (hw->phy.sfp_type != stored_sfp_type)
		hw->phy.sfp_setup_needed = true;

	/* Determine if the QSFP+ PHY is dual speed or not. */
	hw->phy.multispeed_fiber = false;
	if (((comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)) ||
	    ((comp_codes_1g & IXGBE_SFF_1GBASELX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)))
		hw->phy.multispeed_fiber = true;

	/* Determine PHY vendor for optical modules */
	if (comp_codes_10g & (IXGBE_SFF_10GBASESR_CAPABLE |
			      IXGBE_SFF_10GBASELR_CAPABLE)) {
		status = hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE0,
					&oui_bytes[0]);

		if (status != 0)
			goto err_read_i2c_eeprom;

		status = hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE1,
					&oui_bytes[1]);

		if (status != 0)
			goto err_read_i2c_eeprom;

		status = hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE2,
					&oui_bytes[2]);

		if (status != 0)
			goto err_read_i2c_eeprom;

		vendor_oui =
			((oui_bytes[0] << IXGBE_SFF_VENDOR_OUI_BYTE0_SHIFT) |
			 (oui_bytes[1] << IXGBE_SFF_VENDOR_OUI_BYTE1_SHIFT) |
			 (oui_bytes[2] << IXGBE_SFF_VENDOR_OUI_BYTE2_SHIFT));

		if (vendor_oui == IXGBE_SFF_VENDOR_OUI_INTEL)
			hw->phy.type = ixgbe_phy_qsfp_intel;
		else
			hw->phy.type = ixgbe_phy_qsfp_unknown;

		hw->mac.ops.get_device_caps(hw, &enforce_sfp);
		if (!(enforce_sfp & IXGBE_DEVICE_CAPS_ALLOW_ANY_SFP)) {
			/* Make sure we're a supported PHY type */
			if (hw->phy.type == ixgbe_phy_qsfp_intel)
				return 0;
			if (hw->allow_unsupported_sfp) {
				e_warn(drv, "WARNING: Intel (R) Network Connections are quality tested using Intel (R) Ethernet Optics. Using untested modules is not supported and may cause unstable operation or damage to the module or the adapter. Intel Corporation is not responsible for any harm caused by using untested modules.\n");
				return 0;
			}
			hw_dbg(hw, "QSFP module not supported\n");
			hw->phy.type = ixgbe_phy_sfp_unsupported;
			return IXGBE_ERR_SFP_NOT_SUPPORTED;
		}
		return 0;
	}
	return 0;

err_read_i2c_eeprom:
	hw->phy.sfp_type = ixgbe_sfp_type_not_present;
	hw->phy.id = 0;
	hw->phy.type = ixgbe_phy_unknown;

	return IXGBE_ERR_SFP_NOT_PRESENT;
}