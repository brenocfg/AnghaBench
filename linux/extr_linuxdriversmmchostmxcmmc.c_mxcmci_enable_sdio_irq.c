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
typedef  int /*<<< orphan*/  u32 ;
struct mxcmci_host {int use_sdio; int /*<<< orphan*/  lock; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_SDIO_IRQ_EN ; 
 int /*<<< orphan*/  MMC_REG_INT_CNTR ; 
 struct mxcmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mxcmci_readl (struct mxcmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcmci_writel (struct mxcmci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mxcmci_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct mxcmci_host *host = mmc_priv(mmc);
	unsigned long flags;
	u32 int_cntr;

	spin_lock_irqsave(&host->lock, flags);
	host->use_sdio = enable;
	int_cntr = mxcmci_readl(host, MMC_REG_INT_CNTR);

	if (enable)
		int_cntr |= INT_SDIO_IRQ_EN;
	else
		int_cntr &= ~INT_SDIO_IRQ_EN;

	mxcmci_writel(host, int_cntr, MMC_REG_INT_CNTR);
	spin_unlock_irqrestore(&host->lock, flags);
}