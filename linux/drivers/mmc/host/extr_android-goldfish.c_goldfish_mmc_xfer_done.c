#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmc_data {int /*<<< orphan*/  stop; int /*<<< orphan*/  mrq; TYPE_2__* sg; } ;
struct goldfish_mmc_host {int /*<<< orphan*/ * mrq; scalar_t__ sg_len; TYPE_1__* data; int /*<<< orphan*/  virt_base; scalar_t__ dma_in_use; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_5__ {scalar_t__ length; } ;
struct TYPE_4__ {int /*<<< orphan*/  bytes_xfered; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  goldfish_mmc_start_command (struct goldfish_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_from_priv (struct goldfish_mmc_host*) ; 
 int mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (TYPE_2__*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void goldfish_mmc_xfer_done(struct goldfish_mmc_host *host,
				   struct mmc_data *data)
{
	if (host->dma_in_use) {
		enum dma_data_direction dma_data_dir;

		dma_data_dir = mmc_get_dma_dir(data);

		if (dma_data_dir == DMA_FROM_DEVICE) {
			/*
			 * We don't really have DMA, so we need
			 * to copy from our platform driver buffer
			 */
			sg_copy_from_buffer(data->sg, 1, host->virt_base,
					data->sg->length);
		}
		host->data->bytes_xfered += data->sg->length;
		dma_unmap_sg(mmc_dev(mmc_from_priv(host)), data->sg,
			     host->sg_len, dma_data_dir);
	}

	host->data = NULL;
	host->sg_len = 0;

	/*
	 * NOTE:  MMC layer will sometimes poll-wait CMD13 next, issuing
	 * dozens of requests until the card finishes writing data.
	 * It'd be cheaper to just wait till an EOFB interrupt arrives...
	 */

	if (!data->stop) {
		host->mrq = NULL;
		mmc_request_done(mmc_from_priv(host), data->mrq);
		return;
	}

	goldfish_mmc_start_command(host, data->stop);
}