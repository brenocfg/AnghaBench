#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_request {struct mmc_data* data; } ;
struct mmc_data {int blksz; int blocks; int sg_len; TYPE_1__* sg; } ;
struct goldfish_mmc_host {int dma_in_use; int /*<<< orphan*/  virt_base; scalar_t__ dma_done; int /*<<< orphan*/  sg_len; struct mmc_data* data; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GOLDFISH_MMC_WRITE (struct goldfish_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMC_BLOCK_COUNT ; 
 int /*<<< orphan*/  MMC_BLOCK_LENGTH ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_from_priv (struct goldfish_mmc_host*) ; 
 int mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void goldfish_mmc_prepare_data(struct goldfish_mmc_host *host,
				      struct mmc_request *req)
{
	struct mmc_data *data = req->data;
	int block_size;
	unsigned sg_len;
	enum dma_data_direction dma_data_dir;

	host->data = data;
	if (data == NULL) {
		GOLDFISH_MMC_WRITE(host, MMC_BLOCK_LENGTH, 0);
		GOLDFISH_MMC_WRITE(host, MMC_BLOCK_COUNT, 0);
		host->dma_in_use = 0;
		return;
	}

	block_size = data->blksz;

	GOLDFISH_MMC_WRITE(host, MMC_BLOCK_COUNT, data->blocks - 1);
	GOLDFISH_MMC_WRITE(host, MMC_BLOCK_LENGTH, block_size - 1);

	/*
	 * Cope with calling layer confusion; it issues "single
	 * block" writes using multi-block scatterlists.
	 */
	sg_len = (data->blocks == 1) ? 1 : data->sg_len;

	dma_data_dir = mmc_get_dma_dir(data);

	host->sg_len = dma_map_sg(mmc_dev(mmc_from_priv(host)), data->sg,
				  sg_len, dma_data_dir);
	host->dma_done = 0;
	host->dma_in_use = 1;

	if (dma_data_dir == DMA_TO_DEVICE) {
		/*
		 * We don't really have DMA, so we need to copy to our
		 * platform driver buffer
		 */
		sg_copy_to_buffer(data->sg, 1, host->virt_base,
				data->sg->length);
	}
}