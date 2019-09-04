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
typedef  int u8 ;
struct sdhci_host {int flags; int cqe_on; int /*<<< orphan*/  lock; int /*<<< orphan*/  ier; int /*<<< orphan*/  cqe_ier; int /*<<< orphan*/  sdma_boundary; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_BLOCK_SIZE ; 
 int SDHCI_CTRL_ADMA32 ; 
 int SDHCI_CTRL_ADMA64 ; 
 int SDHCI_CTRL_DMA_MASK ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  SDHCI_MAKE_BLKSZ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  SDHCI_TIMEOUT_CONTROL ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
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
	if (host->flags & SDHCI_USE_64_BIT_DMA)
		ctrl |= SDHCI_CTRL_ADMA64;
	else
		ctrl |= SDHCI_CTRL_ADMA32;
	sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);

	sdhci_writew(host, SDHCI_MAKE_BLKSZ(host->sdma_boundary, 512),
		     SDHCI_BLOCK_SIZE);

	/* Set maximum timeout */
	sdhci_writeb(host, 0xE, SDHCI_TIMEOUT_CONTROL);

	host->ier = host->cqe_ier;

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);

	host->cqe_on = true;

	pr_debug("%s: sdhci: CQE on, IRQ mask %#x, IRQ status %#x\n",
		 mmc_hostname(mmc), host->ier,
		 sdhci_readl(host, SDHCI_INT_STATUS));

	mmiowb();
	spin_unlock_irqrestore(&host->lock, flags);
}