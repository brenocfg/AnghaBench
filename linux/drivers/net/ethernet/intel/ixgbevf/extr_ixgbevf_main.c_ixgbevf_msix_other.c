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
struct TYPE_2__ {int get_link_status; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  eims_other; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IXGBE_VTEIMS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_service_event_schedule (struct ixgbevf_adapter*) ; 

__attribute__((used)) static irqreturn_t ixgbevf_msix_other(int irq, void *data)
{
	struct ixgbevf_adapter *adapter = data;
	struct ixgbe_hw *hw = &adapter->hw;

	hw->mac.get_link_status = 1;

	ixgbevf_service_event_schedule(adapter);

	IXGBE_WRITE_REG(hw, IXGBE_VTEIMS, adapter->eims_other);

	return IRQ_HANDLED;
}