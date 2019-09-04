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
typedef  int /*<<< orphan*/  u64 ;
struct mmc_data {int bytes_xfered; int blocks; int blksz; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; scalar_t__ error; } ;
struct cvm_mmc_host {int /*<<< orphan*/  dev; scalar_t__ dma_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MIO_EMM_DMA_FIFO_CFG (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  MIO_EMM_DMA_FIFO_CFG_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int finish_dma_sg(struct cvm_mmc_host *host, struct mmc_data *data)
{
	u64 fifo_cfg;
	int count;

	/* Check if there are any pending requests left */
	fifo_cfg = readq(host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	count = FIELD_GET(MIO_EMM_DMA_FIFO_CFG_COUNT, fifo_cfg);
	if (count)
		dev_err(host->dev, "%u requests still pending\n", count);

	data->bytes_xfered = data->blocks * data->blksz;
	data->error = 0;

	/* Clear and disable FIFO */
	writeq(BIT_ULL(16), host->dma_base + MIO_EMM_DMA_FIFO_CFG(host));
	dma_unmap_sg(host->dev, data->sg, data->sg_len, get_dma_dir(data));
	return 1;
}