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
struct mmc_data {int flags; scalar_t__ host_cookie; int /*<<< orphan*/  sg; } ;
struct jz4740_mmc_host {int /*<<< orphan*/  mmc; TYPE_1__* mem_res; } ;
struct dma_slave_config {scalar_t__ direction; scalar_t__ src_addr; scalar_t__ dst_addr; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  src_addr_width; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ COOKIE_MAPPED ; 
 int DMA_CTRL_ACK ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  JZ4740_MMC_FIFO_HALF_SIZE ; 
 scalar_t__ JZ_REG_MMC_RXFIFO ; 
 scalar_t__ JZ_REG_MMC_TXFIFO ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  dmaengine_slave_config (struct dma_chan*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  jz4740_mmc_dma_unmap (struct jz4740_mmc_host*,struct mmc_data*) ; 
 struct dma_chan* jz4740_mmc_get_dma_chan (struct jz4740_mmc_host*,struct mmc_data*) ; 
 int jz4740_mmc_prepare_dma_data (struct jz4740_mmc_host*,struct mmc_data*,scalar_t__) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_mmc_start_dma_transfer(struct jz4740_mmc_host *host,
					 struct mmc_data *data)
{
	struct dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	struct dma_async_tx_descriptor *desc;
	struct dma_slave_config conf = {
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.src_maxburst = JZ4740_MMC_FIFO_HALF_SIZE,
		.dst_maxburst = JZ4740_MMC_FIFO_HALF_SIZE,
	};
	int sg_count;

	if (data->flags & MMC_DATA_WRITE) {
		conf.direction = DMA_MEM_TO_DEV;
		conf.dst_addr = host->mem_res->start + JZ_REG_MMC_TXFIFO;
	} else {
		conf.direction = DMA_DEV_TO_MEM;
		conf.src_addr = host->mem_res->start + JZ_REG_MMC_RXFIFO;
	}

	sg_count = jz4740_mmc_prepare_dma_data(host, data, COOKIE_MAPPED);
	if (sg_count < 0)
		return sg_count;

	dmaengine_slave_config(chan, &conf);
	desc = dmaengine_prep_slave_sg(chan, data->sg, sg_count,
			conf.direction,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc) {
		dev_err(mmc_dev(host->mmc),
			"Failed to allocate DMA %s descriptor",
			 conf.direction == DMA_MEM_TO_DEV ? "TX" : "RX");
		goto dma_unmap;
	}

	dmaengine_submit(desc);
	dma_async_issue_pending(chan);

	return 0;

dma_unmap:
	if (data->host_cookie == COOKIE_MAPPED)
		jz4740_mmc_dma_unmap(host, data);
	return -ENOMEM;
}