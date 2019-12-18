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
struct ixgbevf_adapter {int /*<<< orphan*/  state; TYPE_1__* pdev; } ;
struct ixgbe_hw {int /*<<< orphan*/ * hw_addr; struct ixgbevf_adapter* back; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_SERVICE_INITED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ixgbevf_service_event_schedule (struct ixgbevf_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_remove_adapter(struct ixgbe_hw *hw)
{
	struct ixgbevf_adapter *adapter = hw->back;

	if (!hw->hw_addr)
		return;
	hw->hw_addr = NULL;
	dev_err(&adapter->pdev->dev, "Adapter removed\n");
	if (test_bit(__IXGBEVF_SERVICE_INITED, &adapter->state))
		ixgbevf_service_event_schedule(adapter);
}