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
struct ixgbevf_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  __IXGBEVF_RESET_REQUESTED ; 
 int /*<<< orphan*/  ixgbevf_service_event_schedule (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_tx_timeout_reset(struct ixgbevf_adapter *adapter)
{
	/* Do the reset outside of interrupt context */
	if (!test_bit(__IXGBEVF_DOWN, &adapter->state)) {
		set_bit(__IXGBEVF_RESET_REQUESTED, &adapter->state);
		ixgbevf_service_event_schedule(adapter);
	}
}