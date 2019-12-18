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
struct pxamci_host {int /*<<< orphan*/  dma_chan_tx; int /*<<< orphan*/  dma_chan_rx; scalar_t__ base; TYPE_1__* pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ *,struct mmc_host*) ;} ;

/* Variables and functions */
 int CLK_IS_OFF ; 
 int DATA_TRAN_DONE ; 
 int END_CMD_RES ; 
 scalar_t__ MMC_I_MASK ; 
 int PRG_DONE ; 
 int RXFIFO_RD_REQ ; 
 int STOP_CMD ; 
 int TXFIFO_WR_REQ ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct pxamci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxamci_stop_clock (struct pxamci_host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct mmc_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pxamci_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);

	if (mmc) {
		struct pxamci_host *host = mmc_priv(mmc);

		mmc_remove_host(mmc);

		if (host->pdata && host->pdata->exit)
			host->pdata->exit(&pdev->dev, mmc);

		pxamci_stop_clock(host);
		writel(TXFIFO_WR_REQ|RXFIFO_RD_REQ|CLK_IS_OFF|STOP_CMD|
		       END_CMD_RES|PRG_DONE|DATA_TRAN_DONE,
		       host->base + MMC_I_MASK);

		dmaengine_terminate_all(host->dma_chan_rx);
		dmaengine_terminate_all(host->dma_chan_tx);
		dma_release_channel(host->dma_chan_rx);
		dma_release_channel(host->dma_chan_tx);

		mmc_free_host(mmc);
	}

	return 0;
}