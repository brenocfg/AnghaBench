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
struct i40e_lldp_variables {int adminstatus; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dcb; } ;
struct i40e_hw {int flags; int port; scalar_t__ dcbx_status; TYPE_2__ mac; TYPE_1__ func_caps; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 scalar_t__ I40E_DCBX_STATUS_DISABLED ; 
 scalar_t__ I40E_DCBX_STATUS_DONE ; 
 scalar_t__ I40E_DCBX_STATUS_IN_PROGRESS ; 
 scalar_t__ I40E_ERR_NOT_READY ; 
 int I40E_HW_FLAG_FW_LLDP_PERSISTENT ; 
 int I40E_LLDP_CURRENT_STATUS_X722_OFFSET ; 
 int I40E_LLDP_CURRENT_STATUS_XL710_OFFSET ; 
 scalar_t__ I40E_MAC_X722 ; 
 scalar_t__ I40E_MAC_XL710 ; 
 scalar_t__ I40E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  I40E_SR_EMP_SR_SETTINGS_PTR ; 
 scalar_t__ i40e_aq_cfg_lldp_mib_change_event (struct i40e_hw*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_get_dcb_config (struct i40e_hw*) ; 
 scalar_t__ i40e_get_dcbx_status (struct i40e_hw*,scalar_t__*) ; 
 scalar_t__ i40e_read_lldp_cfg (struct i40e_hw*,struct i40e_lldp_variables*) ; 
 scalar_t__ i40e_read_nvm_module_data (struct i40e_hw*,int /*<<< orphan*/ ,int,int,int*) ; 

i40e_status i40e_init_dcb(struct i40e_hw *hw, bool enable_mib_change)
{
	i40e_status ret = 0;
	struct i40e_lldp_variables lldp_cfg;
	u8 adminstatus = 0;

	if (!hw->func_caps.dcb)
		return I40E_NOT_SUPPORTED;

	/* Read LLDP NVM area */
	if (hw->flags & I40E_HW_FLAG_FW_LLDP_PERSISTENT) {
		u8 offset = 0;

		if (hw->mac.type == I40E_MAC_XL710)
			offset = I40E_LLDP_CURRENT_STATUS_XL710_OFFSET;
		else if (hw->mac.type == I40E_MAC_X722)
			offset = I40E_LLDP_CURRENT_STATUS_X722_OFFSET;
		else
			return I40E_NOT_SUPPORTED;

		ret = i40e_read_nvm_module_data(hw,
						I40E_SR_EMP_SR_SETTINGS_PTR,
						offset, 1,
						&lldp_cfg.adminstatus);
	} else {
		ret = i40e_read_lldp_cfg(hw, &lldp_cfg);
	}
	if (ret)
		return I40E_ERR_NOT_READY;

	/* Get the LLDP AdminStatus for the current port */
	adminstatus = lldp_cfg.adminstatus >> (hw->port * 4);
	adminstatus &= 0xF;

	/* LLDP agent disabled */
	if (!adminstatus) {
		hw->dcbx_status = I40E_DCBX_STATUS_DISABLED;
		return I40E_ERR_NOT_READY;
	}

	/* Get DCBX status */
	ret = i40e_get_dcbx_status(hw, &hw->dcbx_status);
	if (ret)
		return ret;

	/* Check the DCBX Status */
	if (hw->dcbx_status == I40E_DCBX_STATUS_DONE ||
	    hw->dcbx_status == I40E_DCBX_STATUS_IN_PROGRESS) {
		/* Get current DCBX configuration */
		ret = i40e_get_dcb_config(hw);
		if (ret)
			return ret;
	} else if (hw->dcbx_status == I40E_DCBX_STATUS_DISABLED) {
		return I40E_ERR_NOT_READY;
	}

	/* Configure the LLDP MIB change event */
	if (enable_mib_change)
		ret = i40e_aq_cfg_lldp_mib_change_event(hw, true, NULL);

	return ret;
}