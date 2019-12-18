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
struct mxs_ssp {scalar_t__ base; } ;
struct mxs_mmc_host {int sdio_irq_en; int /*<<< orphan*/  mmc; int /*<<< orphan*/  lock; struct mxs_ssp ssp; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SSP_CTRL0_SDIO_IRQ_CHECK ; 
 int /*<<< orphan*/  BM_SSP_CTRL1_SDIO_IRQ_EN ; 
 int BM_SSP_STATUS_SDIO_IRQ ; 
 scalar_t__ HW_SSP_CTRL0 ; 
 scalar_t__ HW_SSP_CTRL1 (struct mxs_ssp*) ; 
 scalar_t__ HW_SSP_STATUS (struct mxs_ssp*) ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 struct mxs_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_mmc_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct mxs_mmc_host *host = mmc_priv(mmc);
	struct mxs_ssp *ssp = &host->ssp;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	host->sdio_irq_en = enable;

	if (enable) {
		writel(BM_SSP_CTRL0_SDIO_IRQ_CHECK,
		       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);
		writel(BM_SSP_CTRL1_SDIO_IRQ_EN,
		       ssp->base + HW_SSP_CTRL1(ssp) + STMP_OFFSET_REG_SET);
	} else {
		writel(BM_SSP_CTRL0_SDIO_IRQ_CHECK,
		       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);
		writel(BM_SSP_CTRL1_SDIO_IRQ_EN,
		       ssp->base + HW_SSP_CTRL1(ssp) + STMP_OFFSET_REG_CLR);
	}

	spin_unlock_irqrestore(&host->lock, flags);

	if (enable && readl(ssp->base + HW_SSP_STATUS(ssp)) &
			BM_SSP_STATUS_SDIO_IRQ)
		mmc_signal_sdio_irq(host->mmc);

}