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
typedef  int u32 ;
struct sdhci_host {int thread_isr; struct mmc_host* mmc; int /*<<< orphan*/  lock; } ;
struct mmc_host {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* card_event ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SDHCI_INT_CARD_INSERT ; 
 int SDHCI_INT_CARD_REMOVE ; 
 int /*<<< orphan*/  mmc_detect_change (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  sdhci_request_done (struct sdhci_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

__attribute__((used)) static irqreturn_t sdhci_thread_irq(int irq, void *dev_id)
{
	struct sdhci_host *host = dev_id;
	unsigned long flags;
	u32 isr;

	while (!sdhci_request_done(host))
		;

	spin_lock_irqsave(&host->lock, flags);
	isr = host->thread_isr;
	host->thread_isr = 0;
	spin_unlock_irqrestore(&host->lock, flags);

	if (isr & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE)) {
		struct mmc_host *mmc = host->mmc;

		mmc->ops->card_event(mmc);
		mmc_detect_change(mmc, msecs_to_jiffies(200));
	}

	return IRQ_HANDLED;
}