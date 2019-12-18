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
struct tps65090_charger {int /*<<< orphan*/  ac; int /*<<< orphan*/  poll_task; int /*<<< orphan*/  irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 struct tps65090_charger* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65090_charger_remove(struct platform_device *pdev)
{
	struct tps65090_charger *cdata = platform_get_drvdata(pdev);

	if (cdata->irq == -ENXIO)
		kthread_stop(cdata->poll_task);
	power_supply_unregister(cdata->ac);

	return 0;
}