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
struct ixgbe_adapter {int /*<<< orphan*/  service_task; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  __IXGBE_REMOVING ; 
 int /*<<< orphan*/  __IXGBE_SERVICE_SCHED ; 
 int /*<<< orphan*/  ixgbe_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_service_event_schedule(struct ixgbe_adapter *adapter)
{
	if (!test_bit(__IXGBE_DOWN, &adapter->state) &&
	    !test_bit(__IXGBE_REMOVING, &adapter->state) &&
	    !test_and_set_bit(__IXGBE_SERVICE_SCHED, &adapter->state))
		queue_work(ixgbe_wq, &adapter->service_task);
}