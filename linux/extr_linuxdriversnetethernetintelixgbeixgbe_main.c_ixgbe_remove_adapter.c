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
struct ixgbe_hw {int /*<<< orphan*/ * hw_addr; struct ixgbe_adapter* back; } ;
struct ixgbe_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_SERVICE_INITED ; 
 int /*<<< orphan*/  e_dev_err (char*) ; 
 int /*<<< orphan*/  ixgbe_service_event_schedule (struct ixgbe_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_remove_adapter(struct ixgbe_hw *hw)
{
	struct ixgbe_adapter *adapter = hw->back;

	if (!hw->hw_addr)
		return;
	hw->hw_addr = NULL;
	e_dev_err("Adapter removed\n");
	if (test_bit(__IXGBE_SERVICE_INITED, &adapter->state))
		ixgbe_service_event_schedule(adapter);
}