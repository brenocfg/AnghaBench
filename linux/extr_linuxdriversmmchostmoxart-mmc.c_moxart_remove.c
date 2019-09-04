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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct moxart_host {scalar_t__ base; int /*<<< orphan*/  dma_chan_rx; int /*<<< orphan*/  dma_chan_tx; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int CLK_OFF ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_CLOCK_CONTROL ; 
 scalar_t__ REG_INTERRUPT_MASK ; 
 scalar_t__ REG_POWER_CONTROL ; 
 struct mmc_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct moxart_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int moxart_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = dev_get_drvdata(&pdev->dev);
	struct moxart_host *host = mmc_priv(mmc);

	dev_set_drvdata(&pdev->dev, NULL);

	if (mmc) {
		if (!IS_ERR(host->dma_chan_tx))
			dma_release_channel(host->dma_chan_tx);
		if (!IS_ERR(host->dma_chan_rx))
			dma_release_channel(host->dma_chan_rx);
		mmc_remove_host(mmc);
		mmc_free_host(mmc);

		writel(0, host->base + REG_INTERRUPT_MASK);
		writel(0, host->base + REG_POWER_CONTROL);
		writel(readl(host->base + REG_CLOCK_CONTROL) | CLK_OFF,
		       host->base + REG_CLOCK_CONTROL);
	}
	return 0;
}