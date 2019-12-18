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
typedef  int /*<<< orphan*/  u8 ;
struct sdhci_host {int caps1; int flags; int cqe_on; int /*<<< orphan*/  lock; int /*<<< orphan*/  ier; int /*<<< orphan*/  cqe_ier; int /*<<< orphan*/  sdma_boundary; scalar_t__ v4_mode; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_BLOCK_SIZE ; 
 int SDHCI_CAN_DO_ADMA3 ; 
 int /*<<< orphan*/  SDHCI_CTRL_ADMA3 ; 
 int /*<<< orphan*/  SDHCI_CTRL_ADMA32 ; 
 int /*<<< orphan*/  SDHCI_CTRL_ADMA64 ; 
 int /*<<< orphan*/  SDHCI_CTRL_DMA_MASK ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  SDHCI_MAKE_BLKSZ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_set_timeout (struct sdhci_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sdhci_cqe_enable(struct mmc_host *mmc)
{
	struct sdhci_host *host = mmc_priv(mmc);
	unsigned long flags;
	u8 ctrl;

	spin_lock_irqsave(&host->lock, flags);

	ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);
	ctrl &= ~SDHCI_CTRL_DMA_MASK;
	/*
	 * Host from V4.10 supports ADMA3 DMA type.
	 * ADMA3 performs integrated descriptor which is more suitable
	 * for cmd queuing to fetch both command and transfer descriptors.
	 */
	if (host->v4_mode && (host->caps1 & SDHCI_CAN_DO_ADMA3))
		ctrl |= SDHCI_CTRL_ADMA3;
	else if (host->flags & SDHCI_USE_64_BIT_DMA)
		ctrl |= SDHCI_CTRL_ADMA64;
	else
		ctrl |= SDHCI_CTRL_ADMA32;
	sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);

	sdhci_writew(host, SDHCI_MAKE_BLKSZ(host->sdma_boundary, 512),
		     SDHCI_BLOCK_SIZE);

	/* Set maximum timeout */
	sdhci_set_timeout(host, NULL);

	host->ier = host->cqe_ier;

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);

	host->cqe_on = true;

	pr_debug("%s: sdhci: CQE on, IRQ mask %#x, IRQ status %#x\n",
		 mmc_hostname(mmc), host->ier,
		 sdhci_readl(host, SDHCI_INT_STATUS));

	spin_unlock_irqrestore(&host->lock, flags);
}