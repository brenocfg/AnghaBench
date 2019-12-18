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
struct TYPE_3__ {int /*<<< orphan*/  (* setup_link ) (struct ixgbe_hw*,int,int) ;int /*<<< orphan*/  (* get_link_capabilities ) (struct ixgbe_hw*,int*,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {int flags; int /*<<< orphan*/  state; int /*<<< orphan*/  link_check_timeout; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBE_FLAG_NEED_LINK_CONFIG ; 
 int IXGBE_FLAG_NEED_LINK_UPDATE ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  __IXGBE_IN_SFP_INIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_sfp_link_config_subtask(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 cap_speed;
	u32 speed;
	bool autoneg = false;

	if (!(adapter->flags & IXGBE_FLAG_NEED_LINK_CONFIG))
		return;

	/* someone else is in init, wait until next service event */
	if (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
		return;

	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_CONFIG;

	hw->mac.ops.get_link_capabilities(hw, &cap_speed, &autoneg);

	/* advertise highest capable link speed */
	if (!autoneg && (cap_speed & IXGBE_LINK_SPEED_10GB_FULL))
		speed = IXGBE_LINK_SPEED_10GB_FULL;
	else
		speed = cap_speed & (IXGBE_LINK_SPEED_10GB_FULL |
				     IXGBE_LINK_SPEED_1GB_FULL);

	if (hw->mac.ops.setup_link)
		hw->mac.ops.setup_link(hw, speed, true);

	adapter->flags |= IXGBE_FLAG_NEED_LINK_UPDATE;
	adapter->link_check_timeout = jiffies;
	clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);
}