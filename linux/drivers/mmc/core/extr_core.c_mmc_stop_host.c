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
struct TYPE_4__ {scalar_t__ cd_irq; } ;
struct mmc_host {int rescan_disable; TYPE_1__* bus_ops; int /*<<< orphan*/  bus_dead; scalar_t__ pm_flags; int /*<<< orphan*/  detect; TYPE_2__ slot; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* remove ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  mmc_bus_get (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_bus_put (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_detach_bus (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_gpio_set_cd_wake (struct mmc_host*,int) ; 
 int /*<<< orphan*/  mmc_power_off (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

void mmc_stop_host(struct mmc_host *host)
{
	if (host->slot.cd_irq >= 0) {
		mmc_gpio_set_cd_wake(host, false);
		disable_irq(host->slot.cd_irq);
	}

	host->rescan_disable = 1;
	cancel_delayed_work_sync(&host->detect);

	/* clear pm flags now and let card drivers set them as needed */
	host->pm_flags = 0;

	mmc_bus_get(host);
	if (host->bus_ops && !host->bus_dead) {
		/* Calling bus_ops->remove() with a claimed host can deadlock */
		host->bus_ops->remove(host);
		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_power_off(host);
		mmc_release_host(host);
		mmc_bus_put(host);
		return;
	}
	mmc_bus_put(host);

	mmc_claim_host(host);
	mmc_power_off(host);
	mmc_release_host(host);
}