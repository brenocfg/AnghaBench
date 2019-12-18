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
struct sdhci_host {int /*<<< orphan*/ * align_buffer; int /*<<< orphan*/ * adma_table; int /*<<< orphan*/  align_addr; scalar_t__ adma_table_sz; scalar_t__ align_buffer_sz; int /*<<< orphan*/  complete_wq; int /*<<< orphan*/  data_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sdhci_host*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_disable_card_detection (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_error_out_mrqs (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdhci_has_requests (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_led_unregister (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sdhci_remove_host(struct sdhci_host *host, int dead)
{
	struct mmc_host *mmc = host->mmc;
	unsigned long flags;

	if (dead) {
		spin_lock_irqsave(&host->lock, flags);

		host->flags |= SDHCI_DEVICE_DEAD;

		if (sdhci_has_requests(host)) {
			pr_err("%s: Controller removed during "
				" transfer!\n", mmc_hostname(mmc));
			sdhci_error_out_mrqs(host, -ENOMEDIUM);
		}

		spin_unlock_irqrestore(&host->lock, flags);
	}

	sdhci_disable_card_detection(host);

	mmc_remove_host(mmc);

	sdhci_led_unregister(host);

	if (!dead)
		sdhci_do_reset(host, SDHCI_RESET_ALL);

	sdhci_writel(host, 0, SDHCI_INT_ENABLE);
	sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);
	free_irq(host->irq, host);

	del_timer_sync(&host->timer);
	del_timer_sync(&host->data_timer);

	destroy_workqueue(host->complete_wq);

	if (!IS_ERR(mmc->supply.vqmmc))
		regulator_disable(mmc->supply.vqmmc);

	if (host->align_buffer)
		dma_free_coherent(mmc_dev(mmc), host->align_buffer_sz +
				  host->adma_table_sz, host->align_buffer,
				  host->align_addr);

	host->adma_table = NULL;
	host->align_buffer = NULL;
}