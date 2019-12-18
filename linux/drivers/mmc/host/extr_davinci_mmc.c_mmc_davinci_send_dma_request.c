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
struct mmc_davinci_host {scalar_t__ data_dir; int /*<<< orphan*/  mmc; int /*<<< orphan*/  sg_len; struct dma_chan* dma_rx; TYPE_1__* mem_res; struct dma_chan* dma_tx; } ;
struct mmc_data {int /*<<< orphan*/  sg; } ;
struct dma_slave_config {int dst_addr_width; int dst_maxburst; int src_addr_width; int src_maxburst; scalar_t__ src_addr; int /*<<< orphan*/  direction; scalar_t__ dst_addr; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCDRR ; 
 scalar_t__ DAVINCI_MMCDXR ; 
 scalar_t__ DAVINCI_MMC_DATADIR_WRITE ; 
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_slave_config (struct dma_chan*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int rw_threshold ; 

__attribute__((used)) static int mmc_davinci_send_dma_request(struct mmc_davinci_host *host,
		struct mmc_data *data)
{
	struct dma_chan *chan;
	struct dma_async_tx_descriptor *desc;
	int ret = 0;

	if (host->data_dir == DAVINCI_MMC_DATADIR_WRITE) {
		struct dma_slave_config dma_tx_conf = {
			.direction = DMA_MEM_TO_DEV,
			.dst_addr = host->mem_res->start + DAVINCI_MMCDXR,
			.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
			.dst_maxburst =
				rw_threshold / DMA_SLAVE_BUSWIDTH_4_BYTES,
		};
		chan = host->dma_tx;
		dmaengine_slave_config(host->dma_tx, &dma_tx_conf);

		desc = dmaengine_prep_slave_sg(host->dma_tx,
				data->sg,
				host->sg_len,
				DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		if (!desc) {
			dev_dbg(mmc_dev(host->mmc),
				"failed to allocate DMA TX descriptor");
			ret = -1;
			goto out;
		}
	} else {
		struct dma_slave_config dma_rx_conf = {
			.direction = DMA_DEV_TO_MEM,
			.src_addr = host->mem_res->start + DAVINCI_MMCDRR,
			.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
			.src_maxburst =
				rw_threshold / DMA_SLAVE_BUSWIDTH_4_BYTES,
		};
		chan = host->dma_rx;
		dmaengine_slave_config(host->dma_rx, &dma_rx_conf);

		desc = dmaengine_prep_slave_sg(host->dma_rx,
				data->sg,
				host->sg_len,
				DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		if (!desc) {
			dev_dbg(mmc_dev(host->mmc),
				"failed to allocate DMA RX descriptor");
			ret = -1;
			goto out;
		}
	}

	dmaengine_submit(desc);
	dma_async_issue_pending(chan);

out:
	return ret;
}