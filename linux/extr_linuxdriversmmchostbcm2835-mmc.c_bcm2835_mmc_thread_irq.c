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
typedef  int u32 ;
struct bcm2835_host {int thread_isr; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  mmc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SDHCI_INT_CARD_INT ; 
 int SDHCI_SDIO_IRQ_ENABLED ; 
 int /*<<< orphan*/  bcm2835_mmc_enable_sdio_irq_nolock (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  sdio_run_irqs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t bcm2835_mmc_thread_irq(int irq, void *dev_id)
{
	struct bcm2835_host *host = dev_id;
	unsigned long flags;
	u32 isr;

	spin_lock_irqsave(&host->lock, flags);
	isr = host->thread_isr;
	host->thread_isr = 0;
	spin_unlock_irqrestore(&host->lock, flags);

	if (isr & SDHCI_INT_CARD_INT) {
		sdio_run_irqs(host->mmc);

		spin_lock_irqsave(&host->lock, flags);
		if (host->flags & SDHCI_SDIO_IRQ_ENABLED)
			bcm2835_mmc_enable_sdio_irq_nolock(host, true);
		spin_unlock_irqrestore(&host->lock, flags);
	}

	return isr ? IRQ_HANDLED : IRQ_NONE;
}