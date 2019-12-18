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
struct sdio_func {TYPE_1__* card; scalar_t__ irq_handler; } ;
struct sdio_driver {int /*<<< orphan*/  name; int /*<<< orphan*/  (* remove ) (struct sdio_func*) ;} ;
struct device {int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {int caps; } ;
struct TYPE_3__ {TYPE_2__* host; } ;

/* Variables and functions */
 int MMC_CAP_POWER_OFF_CARD ; 
 int /*<<< orphan*/  dev_pm_domain_detach (struct device*,int) ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  stub1 (struct sdio_func*) ; 
 struct sdio_driver* to_sdio_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdio_bus_remove(struct device *dev)
{
	struct sdio_driver *drv = to_sdio_driver(dev->driver);
	struct sdio_func *func = dev_to_sdio_func(dev);

	/* Make sure card is powered before invoking ->remove() */
	if (func->card->host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runtime_get_sync(dev);

	drv->remove(func);

	if (func->irq_handler) {
		pr_warn("WARNING: driver %s did not remove its interrupt handler!\n",
			drv->name);
		sdio_claim_host(func);
		sdio_release_irq(func);
		sdio_release_host(func);
	}

	/* First, undo the increment made directly above */
	if (func->card->host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runtime_put_noidle(dev);

	/* Then undo the runtime PM settings in sdio_bus_probe() */
	if (func->card->host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runtime_put_sync(dev);

	dev_pm_domain_detach(dev, false);

	return 0;
}