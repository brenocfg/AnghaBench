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
struct TYPE_2__ {scalar_t__ requested_mode; } ;
struct ixgbe_hw {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ ixgbe_fc_default ; 
 scalar_t__ ixgbe_fc_full ; 
 int /*<<< orphan*/  ixgbe_setup_fw_link (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_fc_autoneg_fw(struct ixgbe_hw *hw)
{
	if (hw->fc.requested_mode == ixgbe_fc_default)
		hw->fc.requested_mode = ixgbe_fc_full;

	return ixgbe_setup_fw_link(hw);
}