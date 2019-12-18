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
struct mmc_host {int caps; int /*<<< orphan*/  led; int /*<<< orphan*/  class_dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_sdio_irq; } ;

/* Variables and functions */
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_trigger_register_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_add_host_debugfs (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_register_pm_notifier (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_start_host (struct mmc_host*) ; 

int mmc_add_host(struct mmc_host *host)
{
	int err;

	WARN_ON((host->caps & MMC_CAP_SDIO_IRQ) &&
		!host->ops->enable_sdio_irq);

	err = device_add(&host->class_dev);
	if (err)
		return err;

	led_trigger_register_simple(dev_name(&host->class_dev), &host->led);

#ifdef CONFIG_DEBUG_FS
	mmc_add_host_debugfs(host);
#endif

	mmc_start_host(host);
	mmc_register_pm_notifier(host);

	return 0;
}