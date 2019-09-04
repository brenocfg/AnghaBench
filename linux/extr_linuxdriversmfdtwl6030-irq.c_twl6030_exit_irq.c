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
struct TYPE_2__ {scalar_t__ twl_irq; int /*<<< orphan*/  pm_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* twl6030_irq ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 

int twl6030_exit_irq(void)
{
	if (twl6030_irq && twl6030_irq->twl_irq) {
		unregister_pm_notifier(&twl6030_irq->pm_nb);
		free_irq(twl6030_irq->twl_irq, NULL);
		/*
		 * TODO: IRQ domain and allocated nested IRQ descriptors
		 * should be freed somehow here. Now It can't be done, because
		 * child devices will not be deleted during removing of
		 * TWL Core driver and they will still contain allocated
		 * virt IRQs in their Resources tables.
		 * The same prevents us from using devm_request_threaded_irq()
		 * in this module.
		 */
	}
	return 0;
}