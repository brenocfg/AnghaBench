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
struct controller {int /*<<< orphan*/  poll_thread; TYPE_1__* pcie; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ *,struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciehp_isr ; 
 int /*<<< orphan*/  pciehp_ist ; 
 int /*<<< orphan*/  pciehp_poll ; 
 scalar_t__ pciehp_poll_mode ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct controller*) ; 
 int /*<<< orphan*/  slot_name (struct controller*) ; 

__attribute__((used)) static inline int pciehp_request_irq(struct controller *ctrl)
{
	int retval, irq = ctrl->pcie->irq;

	if (pciehp_poll_mode) {
		ctrl->poll_thread = kthread_run(&pciehp_poll, ctrl,
						"pciehp_poll-%s",
						slot_name(ctrl));
		return PTR_ERR_OR_ZERO(ctrl->poll_thread);
	}

	/* Installs the interrupt handler */
	retval = request_threaded_irq(irq, pciehp_isr, pciehp_ist,
				      IRQF_SHARED, "pciehp", ctrl);
	if (retval)
		ctrl_err(ctrl, "Cannot get irq %d for the hotplug controller\n",
			 irq);
	return retval;
}