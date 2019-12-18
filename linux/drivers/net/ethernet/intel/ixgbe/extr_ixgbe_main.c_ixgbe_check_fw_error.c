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
struct TYPE_3__ {scalar_t__ (* fw_recovery_mode ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_FWSM (struct ixgbe_hw*) ; 
 int IXGBE_FWSM_EXT_ERR_IND_MASK ; 
 int IXGBE_FWSM_FW_VAL_BIT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_dev_err (char*) ; 
 int /*<<< orphan*/  e_dev_warn (char*,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static bool ixgbe_check_fw_error(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 fwsm;

	/* read fwsm.ext_err_ind register and log errors */
	fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM(hw));

	if (fwsm & IXGBE_FWSM_EXT_ERR_IND_MASK ||
	    !(fwsm & IXGBE_FWSM_FW_VAL_BIT))
		e_dev_warn("Warning firmware error detected FWSM: 0x%08X\n",
			   fwsm);

	if (hw->mac.ops.fw_recovery_mode && hw->mac.ops.fw_recovery_mode(hw)) {
		e_dev_err("Firmware recovery mode detected. Limiting functionality. Refer to the Intel(R) Ethernet Adapters and Devices User Guide for details on firmware recovery mode.\n");
		return true;
	}

	return false;
}