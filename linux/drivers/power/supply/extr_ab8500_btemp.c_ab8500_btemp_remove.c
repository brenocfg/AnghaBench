#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct ab8500_btemp {int /*<<< orphan*/  btemp_psy; int /*<<< orphan*/  btemp_wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* ab8500_btemp_irq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_irq (int,struct ab8500_btemp*) ; 
 struct ab8500_btemp* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq_byname (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_btemp_remove(struct platform_device *pdev)
{
	struct ab8500_btemp *di = platform_get_drvdata(pdev);
	int i, irq;

	/* Disable interrupts */
	for (i = 0; i < ARRAY_SIZE(ab8500_btemp_irq); i++) {
		irq = platform_get_irq_byname(pdev, ab8500_btemp_irq[i].name);
		free_irq(irq, di);
	}

	/* Delete the work queue */
	destroy_workqueue(di->btemp_wq);

	flush_scheduled_work();
	power_supply_unregister(di->btemp_psy);

	return 0;
}