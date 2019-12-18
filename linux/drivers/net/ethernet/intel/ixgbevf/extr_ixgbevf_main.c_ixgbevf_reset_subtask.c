#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ixgbevf_adapter {int /*<<< orphan*/  tx_timeout_count; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  __IXGBEVF_REMOVING ; 
 int /*<<< orphan*/  __IXGBEVF_RESETTING ; 
 int /*<<< orphan*/  __IXGBEVF_RESET_REQUESTED ; 
 int /*<<< orphan*/  ixgbevf_reinit_locked (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_reset_subtask(struct ixgbevf_adapter *adapter)
{
	if (!test_and_clear_bit(__IXGBEVF_RESET_REQUESTED, &adapter->state))
		return;

	rtnl_lock();
	/* If we're already down or resetting, just bail */
	if (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_REMOVING, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state)) {
		rtnl_unlock();
		return;
	}

	adapter->tx_timeout_count++;

	ixgbevf_reinit_locked(adapter);
	rtnl_unlock();
}