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
struct mmc_request {int /*<<< orphan*/  cmd; } ;
struct mmc_omap_host {struct dma_chan* dma_rx; struct dma_chan* dma_tx; TYPE_1__* data; scalar_t__ dma_in_use; struct mmc_request* mrq; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int /*<<< orphan*/  mmc_omap_prepare_data (struct mmc_omap_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_omap_start_command (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_omap_start_request(struct mmc_omap_host *host,
				   struct mmc_request *req)
{
	BUG_ON(host->mrq != NULL);

	host->mrq = req;

	/* only touch fifo AFTER the controller readies it */
	mmc_omap_prepare_data(host, req);
	mmc_omap_start_command(host, req->cmd);
	if (host->dma_in_use) {
		struct dma_chan *c = host->data->flags & MMC_DATA_WRITE ?
				host->dma_tx : host->dma_rx;

		dma_async_issue_pending(c);
	}
}