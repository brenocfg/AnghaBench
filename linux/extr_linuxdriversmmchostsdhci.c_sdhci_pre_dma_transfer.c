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
struct sdhci_host {unsigned int bounce_buffer_size; TYPE_1__* mmc; int /*<<< orphan*/  bounce_addr; scalar_t__ bounce_buffer; } ;
struct mmc_data {int host_cookie; int sg_count; unsigned int blksz; unsigned int blocks; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int COOKIE_PRE_MAPPED ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int EIO ; 
 int ENOSPC ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_1__*) ; 
 scalar_t__ mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int sdhci_pre_dma_transfer(struct sdhci_host *host,
				  struct mmc_data *data, int cookie)
{
	int sg_count;

	/*
	 * If the data buffers are already mapped, return the previous
	 * dma_map_sg() result.
	 */
	if (data->host_cookie == COOKIE_PRE_MAPPED)
		return data->sg_count;

	/* Bounce write requests to the bounce buffer */
	if (host->bounce_buffer) {
		unsigned int length = data->blksz * data->blocks;

		if (length > host->bounce_buffer_size) {
			pr_err("%s: asked for transfer of %u bytes exceeds bounce buffer %u bytes\n",
			       mmc_hostname(host->mmc), length,
			       host->bounce_buffer_size);
			return -EIO;
		}
		if (mmc_get_dma_dir(data) == DMA_TO_DEVICE) {
			/* Copy the data to the bounce buffer */
			sg_copy_to_buffer(data->sg, data->sg_len,
					  host->bounce_buffer,
					  length);
		}
		/* Switch ownership to the DMA */
		dma_sync_single_for_device(host->mmc->parent,
					   host->bounce_addr,
					   host->bounce_buffer_size,
					   mmc_get_dma_dir(data));
		/* Just a dummy value */
		sg_count = 1;
	} else {
		/* Just access the data directly from memory */
		sg_count = dma_map_sg(mmc_dev(host->mmc),
				      data->sg, data->sg_len,
				      mmc_get_dma_dir(data));
	}

	if (sg_count == 0)
		return -ENOSPC;

	data->sg_count = sg_count;
	data->host_cookie = cookie;

	return sg_count;
}