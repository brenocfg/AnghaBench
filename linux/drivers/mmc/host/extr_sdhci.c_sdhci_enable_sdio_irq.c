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
struct sdhci_host {TYPE_1__* mmc; int /*<<< orphan*/  lock; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_enable_sdio_irq_nolock (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sdhci_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct sdhci_host *host = mmc_priv(mmc);
	unsigned long flags;

	if (enable)
		pm_runtime_get_noresume(host->mmc->parent);

	spin_lock_irqsave(&host->lock, flags);
	sdhci_enable_sdio_irq_nolock(host, enable);
	spin_unlock_irqrestore(&host->lock, flags);

	if (!enable)
		pm_runtime_put_noidle(host->mmc->parent);
}