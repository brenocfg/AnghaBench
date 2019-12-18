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
struct mmc_host {scalar_t__ retune_period; int /*<<< orphan*/  card; int /*<<< orphan*/  sdio_irq_work; scalar_t__ sdio_irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ mmc_card_keep_power (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_card_set_suspended (int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_card_wake_sdio_irq (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_off (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_retune_needed (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_retune_timer_stop (struct mmc_host*) ; 
 int /*<<< orphan*/  sdio_disable_wide (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_sdio_suspend(struct mmc_host *host)
{
	WARN_ON(host->sdio_irqs && !mmc_card_keep_power(host));

	/* Prevent processing of SDIO IRQs in suspended state. */
	mmc_card_set_suspended(host->card);
	cancel_delayed_work_sync(&host->sdio_irq_work);

	mmc_claim_host(host);

	if (mmc_card_keep_power(host) && mmc_card_wake_sdio_irq(host))
		sdio_disable_wide(host->card);

	if (!mmc_card_keep_power(host)) {
		mmc_power_off(host);
	} else if (host->retune_period) {
		mmc_retune_timer_stop(host);
		mmc_retune_needed(host);
	}

	mmc_release_host(host);

	return 0;
}