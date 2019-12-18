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
struct sfp {int /*<<< orphan*/  timeout; int /*<<< orphan*/  poll; int /*<<< orphan*/ * gpio_irq; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int GPIO_MAX ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sfp*) ; 
 struct sfp* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void sfp_shutdown(struct platform_device *pdev)
{
	struct sfp *sfp = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < GPIO_MAX; i++) {
		if (!sfp->gpio_irq[i])
			continue;

		devm_free_irq(sfp->dev, sfp->gpio_irq[i], sfp);
	}

	cancel_delayed_work_sync(&sfp->poll);
	cancel_delayed_work_sync(&sfp->timeout);
}