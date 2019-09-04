#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wbsd_host {scalar_t__ dma; TYPE_2__* mrq; int /*<<< orphan*/  mmc; } ;
struct mmc_data {int bytes_xfered; int blksz; int error; int flags; scalar_t__ stop; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int blocks; int blksz; } ;

/* Variables and functions */
 int EIO ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int WBSD_BLOCK_READ ; 
 int WBSD_BLOCK_WRITE ; 
 int /*<<< orphan*/  WBSD_IDX_DMA ; 
 int /*<<< orphan*/  WBSD_IDX_STATUS ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (scalar_t__) ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int get_dma_residue (scalar_t__) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  wbsd_dma_to_sg (struct wbsd_host*,struct mmc_data*) ; 
 int wbsd_read_index (struct wbsd_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbsd_request_end (struct wbsd_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  wbsd_send_command (struct wbsd_host*,scalar_t__) ; 
 int /*<<< orphan*/  wbsd_write_index (struct wbsd_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbsd_finish_data(struct wbsd_host *host, struct mmc_data *data)
{
	unsigned long dmaflags;
	int count;
	u8 status;

	WARN_ON(host->mrq == NULL);

	/*
	 * Send a stop command if needed.
	 */
	if (data->stop)
		wbsd_send_command(host, data->stop);

	/*
	 * Wait for the controller to leave data
	 * transfer state.
	 */
	do {
		status = wbsd_read_index(host, WBSD_IDX_STATUS);
	} while (status & (WBSD_BLOCK_READ | WBSD_BLOCK_WRITE));

	/*
	 * DMA transfer?
	 */
	if (host->dma >= 0) {
		/*
		 * Disable DMA on the host.
		 */
		wbsd_write_index(host, WBSD_IDX_DMA, 0);

		/*
		 * Turn of ISA DMA controller.
		 */
		dmaflags = claim_dma_lock();
		disable_dma(host->dma);
		clear_dma_ff(host->dma);
		count = get_dma_residue(host->dma);
		release_dma_lock(dmaflags);

		data->bytes_xfered = host->mrq->data->blocks *
			host->mrq->data->blksz - count;
		data->bytes_xfered -= data->bytes_xfered % data->blksz;

		/*
		 * Any leftover data?
		 */
		if (count) {
			pr_err("%s: Incomplete DMA transfer. "
				"%d bytes left.\n",
				mmc_hostname(host->mmc), count);

			if (!data->error)
				data->error = -EIO;
		} else {
			/*
			 * Transfer data from DMA buffer to
			 * SG list.
			 */
			if (data->flags & MMC_DATA_READ)
				wbsd_dma_to_sg(host, data);
		}

		if (data->error) {
			if (data->bytes_xfered)
				data->bytes_xfered -= data->blksz;
		}
	}

	wbsd_request_end(host, host->mrq);
}