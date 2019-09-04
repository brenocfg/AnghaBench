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
struct mmc_host {int caps; int caps2; int /*<<< orphan*/  pm_flags; TYPE_1__* ops; int /*<<< orphan*/  sdio_irq_thread; scalar_t__ sdio_irqs; TYPE_2__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  ocr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_sdio_irq ) (struct mmc_host*,int) ;} ;

/* Variables and functions */
 int MMC_CAP2_SDIO_IRQ_NOTHREAD ; 
 int MMC_CAP_POWER_OFF_CARD ; 
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  MMC_PM_KEEP_POWER ; 
 scalar_t__ mmc_card_is_removable (struct mmc_host*) ; 
 scalar_t__ mmc_card_keep_power (struct mmc_host*) ; 
 scalar_t__ mmc_card_wake_sdio_irq (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_up (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int mmc_sdio_reinit_card (struct mmc_host*,scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int sdio_enable_4bit_bus (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*,int) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_sdio_resume(struct mmc_host *host)
{
	int err = 0;

	/* Basic card reinitialization. */
	mmc_claim_host(host);

	/* Restore power if needed */
	if (!mmc_card_keep_power(host)) {
		mmc_power_up(host, host->card->ocr);
		/*
		 * Tell runtime PM core we just powered up the card,
		 * since it still believes the card is powered off.
		 * Note that currently runtime PM is only enabled
		 * for SDIO cards that are MMC_CAP_POWER_OFF_CARD
		 */
		if (host->caps & MMC_CAP_POWER_OFF_CARD) {
			pm_runtime_disable(&host->card->dev);
			pm_runtime_set_active(&host->card->dev);
			pm_runtime_enable(&host->card->dev);
		}
	}

	/* No need to reinitialize powered-resumed nonremovable cards */
	if (mmc_card_is_removable(host) || !mmc_card_keep_power(host)) {
		err = mmc_sdio_reinit_card(host, mmc_card_keep_power(host));
	} else if (mmc_card_keep_power(host) && mmc_card_wake_sdio_irq(host)) {
		/* We may have switched to 1-bit mode during suspend */
		err = sdio_enable_4bit_bus(host->card);
	}

	if (!err && host->sdio_irqs) {
		if (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD))
			wake_up_process(host->sdio_irq_thread);
		else if (host->caps & MMC_CAP_SDIO_IRQ)
			host->ops->enable_sdio_irq(host, 1);
	}

	mmc_release_host(host);

	host->pm_flags &= ~MMC_PM_KEEP_POWER;
	return err;
}