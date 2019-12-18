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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct fjes_hw {TYPE_1__ hw_res; } ;
struct fjes_adapter {int interrupt_watch_enable; int irq_registered; struct fjes_hw hw; int /*<<< orphan*/  interrupt_watch_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ICTL_MASK_ALL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fjes_hw_set_irqmask (struct fjes_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fjes_adapter*) ; 

__attribute__((used)) static void fjes_free_irq(struct fjes_adapter *adapter)
{
	struct fjes_hw *hw = &adapter->hw;

	adapter->interrupt_watch_enable = false;
	cancel_delayed_work_sync(&adapter->interrupt_watch_task);

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_ALL, true);

	if (adapter->irq_registered) {
		free_irq(adapter->hw.hw_res.irq, adapter);
		adapter->irq_registered = false;
	}
}