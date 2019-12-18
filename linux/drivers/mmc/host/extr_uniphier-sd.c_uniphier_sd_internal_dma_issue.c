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
struct tmio_mmc_host {scalar_t__ ctl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMIO_STAT_DATAEND ; 
 scalar_t__ UNIPHIER_SD_DMA_CTL ; 
 int /*<<< orphan*/  UNIPHIER_SD_DMA_CTL_START ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmio_mmc_enable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_sd_dma_endisable (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_sd_internal_dma_issue(unsigned long arg)
{
	struct tmio_mmc_host *host = (void *)arg;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	tmio_mmc_enable_mmc_irqs(host, TMIO_STAT_DATAEND);
	spin_unlock_irqrestore(&host->lock, flags);

	uniphier_sd_dma_endisable(host, 1);
	writel(UNIPHIER_SD_DMA_CTL_START, host->ctl + UNIPHIER_SD_DMA_CTL);
}