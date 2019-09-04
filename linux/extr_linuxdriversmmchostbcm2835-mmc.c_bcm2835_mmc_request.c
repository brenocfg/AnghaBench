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
struct mmc_request {TYPE_1__* cmd; TYPE_1__* sbc; } ;
struct mmc_host {int dummy; } ;
struct bcm2835_host {int flags; scalar_t__ use_dma; int /*<<< orphan*/  lock; struct mmc_request* mrq; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int SDHCI_AUTO_CMD23 ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_send_command (struct bcm2835_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  bcm2835_mmc_transfer_dma (struct bcm2835_host*) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct bcm2835_host *host;
	unsigned long flags;

	host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);

	WARN_ON(host->mrq != NULL);

	host->mrq = mrq;

	if (mrq->sbc && !(host->flags & SDHCI_AUTO_CMD23))
		bcm2835_mmc_send_command(host, mrq->sbc);
	else
		bcm2835_mmc_send_command(host, mrq->cmd);

	mmiowb();
	spin_unlock_irqrestore(&host->lock, flags);

	if (!(mrq->sbc && !(host->flags & SDHCI_AUTO_CMD23)) && mrq->cmd->data && host->use_dma) {
		/* DMA transfer starts now, PIO starts after interrupt */
		bcm2835_mmc_transfer_dma(host);
	}
}