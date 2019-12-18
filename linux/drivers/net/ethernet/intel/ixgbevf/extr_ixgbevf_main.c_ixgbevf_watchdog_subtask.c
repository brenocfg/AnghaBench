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
struct ixgbevf_adapter {scalar_t__ link_up; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  __IXGBEVF_RESETTING ; 
 int /*<<< orphan*/  ixgbevf_update_stats (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_watchdog_link_is_down (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_watchdog_link_is_up (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_watchdog_update_link (struct ixgbevf_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_watchdog_subtask(struct ixgbevf_adapter *adapter)
{
	/* if interface is down do nothing */
	if (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state))
		return;

	ixgbevf_watchdog_update_link(adapter);

	if (adapter->link_up)
		ixgbevf_watchdog_link_is_up(adapter);
	else
		ixgbevf_watchdog_link_is_down(adapter);

	ixgbevf_update_stats(adapter);
}