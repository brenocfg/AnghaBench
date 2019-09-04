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
struct mmc_davinci_host {void* dma_rx; void* dma_tx; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_chan (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int davinci_acquire_dma_channels(struct mmc_davinci_host *host)
{
	host->dma_tx = dma_request_chan(mmc_dev(host->mmc), "tx");
	if (IS_ERR(host->dma_tx)) {
		dev_err(mmc_dev(host->mmc), "Can't get dma_tx channel\n");
		return PTR_ERR(host->dma_tx);
	}

	host->dma_rx = dma_request_chan(mmc_dev(host->mmc), "rx");
	if (IS_ERR(host->dma_rx)) {
		dev_err(mmc_dev(host->mmc), "Can't get dma_rx channel\n");
		dma_release_channel(host->dma_tx);
		return PTR_ERR(host->dma_rx);
	}

	return 0;
}