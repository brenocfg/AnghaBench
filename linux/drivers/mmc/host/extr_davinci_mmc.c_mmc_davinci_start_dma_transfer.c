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
struct mmc_davinci_host {int sg_len; int do_dma; int /*<<< orphan*/  mmc; } ;
struct mmc_data {int /*<<< orphan*/  sg_len; scalar_t__ sg; } ;

/* Variables and functions */
 int dma_map_sg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_davinci_send_dma_request (struct mmc_davinci_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 
 int rw_threshold ; 
 int sg_dma_len (scalar_t__) ; 

__attribute__((used)) static int mmc_davinci_start_dma_transfer(struct mmc_davinci_host *host,
		struct mmc_data *data)
{
	int i;
	int mask = rw_threshold - 1;
	int ret = 0;

	host->sg_len = dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
				  mmc_get_dma_dir(data));

	/* no individual DMA segment should need a partial FIFO */
	for (i = 0; i < host->sg_len; i++) {
		if (sg_dma_len(data->sg + i) & mask) {
			dma_unmap_sg(mmc_dev(host->mmc),
				     data->sg, data->sg_len,
				     mmc_get_dma_dir(data));
			return -1;
		}
	}

	host->do_dma = 1;
	ret = mmc_davinci_send_dma_request(host, data);

	return ret;
}