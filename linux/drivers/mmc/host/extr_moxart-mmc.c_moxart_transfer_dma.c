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
struct moxart_host {scalar_t__ data_len; scalar_t__ data_remain; int /*<<< orphan*/  timeout; int /*<<< orphan*/  dma_complete; struct dma_async_tx_descriptor* tx_desc; int /*<<< orphan*/  mmc; struct dma_chan* dma_chan_rx; struct dma_chan* dma_chan_tx; } ;
struct mmc_data {scalar_t__ bytes_xfered; int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {struct moxart_host* callback_param; int /*<<< orphan*/  callback; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 scalar_t__ dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  moxart_dma_complete ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void moxart_transfer_dma(struct mmc_data *data, struct moxart_host *host)
{
	u32 len, dir_slave;
	long dma_time;
	struct dma_async_tx_descriptor *desc = NULL;
	struct dma_chan *dma_chan;

	if (host->data_len == data->bytes_xfered)
		return;

	if (data->flags & MMC_DATA_WRITE) {
		dma_chan = host->dma_chan_tx;
		dir_slave = DMA_MEM_TO_DEV;
	} else {
		dma_chan = host->dma_chan_rx;
		dir_slave = DMA_DEV_TO_MEM;
	}

	len = dma_map_sg(dma_chan->device->dev, data->sg,
			 data->sg_len, mmc_get_dma_dir(data));

	if (len > 0) {
		desc = dmaengine_prep_slave_sg(dma_chan, data->sg,
					       len, dir_slave,
					       DMA_PREP_INTERRUPT |
					       DMA_CTRL_ACK);
	} else {
		dev_err(mmc_dev(host->mmc), "dma_map_sg returned zero length\n");
	}

	if (desc) {
		host->tx_desc = desc;
		desc->callback = moxart_dma_complete;
		desc->callback_param = host;
		dmaengine_submit(desc);
		dma_async_issue_pending(dma_chan);
	}

	data->bytes_xfered += host->data_remain;

	dma_time = wait_for_completion_interruptible_timeout(
		   &host->dma_complete, host->timeout);

	dma_unmap_sg(dma_chan->device->dev,
		     data->sg, data->sg_len,
		     mmc_get_dma_dir(data));
}