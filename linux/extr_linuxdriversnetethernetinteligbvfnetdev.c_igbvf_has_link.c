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
struct TYPE_3__ {scalar_t__ (* check_for_link ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  get_link_status; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ mac; int /*<<< orphan*/  mbx_lock; } ;
struct igbvf_adapter {int /*<<< orphan*/  reset_task; scalar_t__ last_reset; int /*<<< orphan*/  state; struct e1000_hw hw; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int HZ ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool igbvf_has_link(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	s32 ret_val = E1000_SUCCESS;
	bool link_active;

	/* If interface is down, stay link down */
	if (test_bit(__IGBVF_DOWN, &adapter->state))
		return false;

	spin_lock_bh(&hw->mbx_lock);

	ret_val = hw->mac.ops.check_for_link(hw);

	spin_unlock_bh(&hw->mbx_lock);

	link_active = !hw->mac.get_link_status;

	/* if check for link returns error we will need to reset */
	if (ret_val && time_after(jiffies, adapter->last_reset + (10 * HZ)))
		schedule_work(&adapter->reset_task);

	return link_active;
}