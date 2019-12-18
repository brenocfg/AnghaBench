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
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {TYPE_1__ hw_res; } ;
struct fjes_adapter {int interrupt_watch_enable; int irq_registered; TYPE_2__ hw; int /*<<< orphan*/  interrupt_watch_task; int /*<<< orphan*/  control_wq; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FJES_IRQ_WATCH_DELAY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fjes_intr ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fjes_adapter*) ; 

__attribute__((used)) static int fjes_request_irq(struct fjes_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int result = -1;

	adapter->interrupt_watch_enable = true;
	if (!delayed_work_pending(&adapter->interrupt_watch_task)) {
		queue_delayed_work(adapter->control_wq,
				   &adapter->interrupt_watch_task,
				   FJES_IRQ_WATCH_DELAY);
	}

	if (!adapter->irq_registered) {
		result = request_irq(adapter->hw.hw_res.irq, fjes_intr,
				     IRQF_SHARED, netdev->name, adapter);
		if (result)
			adapter->irq_registered = false;
		else
			adapter->irq_registered = true;
	}

	return result;
}