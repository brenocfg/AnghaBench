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
struct TYPE_2__ {int mc_filter_type; } ;
struct ixgbe_addr_filter_info {scalar_t__ mta_in_use; } ;
struct ixgbe_hw {TYPE_1__ mac; struct ixgbe_addr_filter_info addr_ctrl; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_MCSTCTRL ; 
 int IXGBE_MCSTCTRL_MFE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

s32 ixgbe_enable_mc_generic(struct ixgbe_hw *hw)
{
	struct ixgbe_addr_filter_info *a = &hw->addr_ctrl;

	if (a->mta_in_use > 0)
		IXGBE_WRITE_REG(hw, IXGBE_MCSTCTRL, IXGBE_MCSTCTRL_MFE |
				hw->mac.mc_filter_type);

	return 0;
}