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
struct ixgbe_adapter {int /*<<< orphan*/  tx_timeout_count; int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  __IXGBE_REMOVING ; 
 int /*<<< orphan*/  __IXGBE_RESETTING ; 
 int /*<<< orphan*/  __IXGBE_RESET_REQUESTED ; 
 int /*<<< orphan*/  ixgbe_dump (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_reinit_locked (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_reset_subtask(struct ixgbe_adapter *adapter)
{
	if (!test_and_clear_bit(__IXGBE_RESET_REQUESTED, &adapter->state))
		return;

	rtnl_lock();
	/* If we're already down, removing or resetting, just bail */
	if (test_bit(__IXGBE_DOWN, &adapter->state) ||
	    test_bit(__IXGBE_REMOVING, &adapter->state) ||
	    test_bit(__IXGBE_RESETTING, &adapter->state)) {
		rtnl_unlock();
		return;
	}

	ixgbe_dump(adapter);
	netdev_err(adapter->netdev, "Reset adapter\n");
	adapter->tx_timeout_count++;

	ixgbe_reinit_locked(adapter);
	rtnl_unlock();
}