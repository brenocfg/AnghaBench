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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,scalar_t__,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_FW_LESM_PARAMETERS_PTR ; 
 scalar_t__ IXGBE_FW_LESM_STATE_1 ; 
 int IXGBE_FW_LESM_STATE_ENABLED ; 
 scalar_t__ IXGBE_FW_PTR ; 
 scalar_t__ stub1 (struct ixgbe_hw*,scalar_t__,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,scalar_t__,int*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,scalar_t__,int*) ; 

__attribute__((used)) static bool ixgbe_verify_lesm_fw_enabled_82599(struct ixgbe_hw *hw)
{
	u16 fw_offset, fw_lesm_param_offset, fw_lesm_state;
	s32 status;

	/* get the offset to the Firmware Module block */
	status = hw->eeprom.ops.read(hw, IXGBE_FW_PTR, &fw_offset);

	if (status || fw_offset == 0 || fw_offset == 0xFFFF)
		return false;

	/* get the offset to the LESM Parameters block */
	status = hw->eeprom.ops.read(hw, (fw_offset +
				     IXGBE_FW_LESM_PARAMETERS_PTR),
				     &fw_lesm_param_offset);

	if (status ||
	    fw_lesm_param_offset == 0 || fw_lesm_param_offset == 0xFFFF)
		return false;

	/* get the lesm state word */
	status = hw->eeprom.ops.read(hw, (fw_lesm_param_offset +
				     IXGBE_FW_LESM_STATE_1),
				     &fw_lesm_state);

	if (!status && (fw_lesm_state & IXGBE_FW_LESM_STATE_ENABLED))
		return true;

	return false;
}