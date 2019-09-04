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
typedef  scalar_t__ u32 ;
struct sunxi_mmc_host {TYPE_1__* mmc; int /*<<< orphan*/  lock; scalar_t__ sdio_imask; int /*<<< orphan*/  dev; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IMASK ; 
 scalar_t__ SDXC_SDIO_INTERRUPT ; 
 struct sunxi_mmc_host* mmc_priv (struct mmc_host*) ; 
 scalar_t__ mmc_readl (struct sunxi_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_writel (struct sunxi_mmc_host*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sunxi_mmc_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct sunxi_mmc_host *host = mmc_priv(mmc);
	unsigned long flags;
	u32 imask;

	if (enable)
		pm_runtime_get_noresume(host->dev);

	spin_lock_irqsave(&host->lock, flags);

	imask = mmc_readl(host, REG_IMASK);
	if (enable) {
		host->sdio_imask = SDXC_SDIO_INTERRUPT;
		imask |= SDXC_SDIO_INTERRUPT;
	} else {
		host->sdio_imask = 0;
		imask &= ~SDXC_SDIO_INTERRUPT;
	}
	mmc_writel(host, REG_IMASK, imask);
	spin_unlock_irqrestore(&host->lock, flags);

	if (!enable)
		pm_runtime_put_noidle(host->mmc->parent);
}