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
struct controller {TYPE_1__* pcie; int /*<<< orphan*/  poll_thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct controller*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ pciehp_poll_mode ; 

__attribute__((used)) static inline void pciehp_free_irq(struct controller *ctrl)
{
	if (pciehp_poll_mode)
		kthread_stop(ctrl->poll_thread);
	else
		free_irq(ctrl->pcie->irq, ctrl);
}