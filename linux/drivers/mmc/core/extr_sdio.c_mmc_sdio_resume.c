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
struct mmc_host {int caps; int caps2; int /*<<< orphan*/  pm_flags; int /*<<< orphan*/  sdio_irq_work; int /*<<< orphan*/  sdio_irq_thread; scalar_t__ sdio_irqs; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  ocr; } ;

/* Variables and functions */
 int MMC_CAP2_SDIO_IRQ_NOTHREAD ; 
 int MMC_CAP_POWER_OFF_CARD ; 
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  MMC_PM_KEEP_POWER ; 
 int /*<<< orphan*/  mmc_card_clr_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_card_keep_power (struct mmc_host*) ; 
 scalar_t__ mmc_card_wake_sdio_irq (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_up (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int mmc_sdio_reinit_card (struct mmc_host*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sdio_enable_4bit_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  system_wq ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_sdio_resume(struct mmc_host *host)
{
	int err = 0;

	/* Basic card reinitialization. */
	mmc_claim_host(host);

	/*
	 * Restore power and reinitialize the card when needed. Note that a
	 * removable card is checked from a detect work later on in the resume
	 * process.
	 */
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
		err = mmc_sdio_reinit_card(host);
	} else if (mmc_card_wake_sdio_irq(host)) {
		/* We may have switched to 1-bit mode during suspend */
		err = sdio_enable_4bit_bus(host->card);
	}

	if (err)
		goto out;

	/* Allow SDIO IRQs to be processed again. */
	mmc_card_clr_suspended(host->card);

	if (host->sdio_irqs) {
		if (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD))
			wake_up_process(host->sdio_irq_thread);
		else if (host->caps & MMC_CAP_SDIO_IRQ)
			queue_delayed_work(system_wq, &host->sdio_irq_work, 0);
	}

out:
	mmc_release_host(host);

	host->pm_flags &= ~MMC_PM_KEEP_POWER;
	return err;
}