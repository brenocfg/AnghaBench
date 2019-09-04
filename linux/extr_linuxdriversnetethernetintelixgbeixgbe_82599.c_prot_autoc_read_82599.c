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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 scalar_t__ IXGBE_ERR_SWFW_SYNC ; 
 int /*<<< orphan*/  IXGBE_GSSR_MAC_CSR_SM ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_verify_lesm_fw_enabled_82599 (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 prot_autoc_read_82599(struct ixgbe_hw *hw, bool *locked,
				 u32 *reg_val)
{
	s32 ret_val;

	*locked = false;
	/* If LESM is on then we need to hold the SW/FW semaphore. */
	if (ixgbe_verify_lesm_fw_enabled_82599(hw)) {
		ret_val = hw->mac.ops.acquire_swfw_sync(hw,
					IXGBE_GSSR_MAC_CSR_SM);
		if (ret_val)
			return IXGBE_ERR_SWFW_SYNC;

		*locked = true;
	}

	*reg_val = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	return 0;
}