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
struct mmc_host {int dummy; } ;
struct bcm2835_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_SDIO_IRQ_ENABLED ; 
 int /*<<< orphan*/  bcm2835_mmc_enable_sdio_irq_nolock (struct bcm2835_host*,int) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_mmc_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct bcm2835_host *host = mmc_priv(mmc);
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	if (enable)
		host->flags |= SDHCI_SDIO_IRQ_ENABLED;
	else
		host->flags &= ~SDHCI_SDIO_IRQ_ENABLED;

	bcm2835_mmc_enable_sdio_irq_nolock(host, enable);
	spin_unlock_irqrestore(&host->lock, flags);
}