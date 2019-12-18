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
struct TYPE_3__ {scalar_t__ (* check_link ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbevf_adapter {int link_up; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  state; scalar_t__ last_reset; int /*<<< orphan*/  mbx_lock; struct ixgbe_hw hw; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  __IXGBEVF_RESET_REQUESTED ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ixgbevf_watchdog_update_link(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 link_speed = adapter->link_speed;
	bool link_up = adapter->link_up;
	s32 err;

	spin_lock_bh(&adapter->mbx_lock);

	err = hw->mac.ops.check_link(hw, &link_speed, &link_up, false);

	spin_unlock_bh(&adapter->mbx_lock);

	/* if check for link returns error we will need to reset */
	if (err && time_after(jiffies, adapter->last_reset + (10 * HZ))) {
		set_bit(__IXGBEVF_RESET_REQUESTED, &adapter->state);
		link_up = false;
	}

	adapter->link_up = link_up;
	adapter->link_speed = link_speed;
}