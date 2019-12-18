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
struct pxamci_host {TYPE_2__* mrq; int /*<<< orphan*/  cmdat; struct mmc_data* data; int /*<<< orphan*/  dma_dir; struct dma_chan* dma_chan_tx; struct dma_chan* dma_chan_rx; } ;
struct mmc_data {int flags; int bytes_xfered; int blocks; int blksz; int /*<<< orphan*/  error; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_4__ {scalar_t__ stop; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TRAN_DONE ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_DATA_READ ; 
 unsigned int STAT_CRC_READ_ERROR ; 
 unsigned int STAT_CRC_WRITE_ERROR ; 
 unsigned int STAT_READ_TIME_OUT ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxamci_disable_irq (struct pxamci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxamci_finish_request (struct pxamci_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  pxamci_start_cmd (struct pxamci_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxamci_stop_clock (struct pxamci_host*) ; 

__attribute__((used)) static int pxamci_data_done(struct pxamci_host *host, unsigned int stat)
{
	struct mmc_data *data = host->data;
	struct dma_chan *chan;

	if (!data)
		return 0;

	if (data->flags & MMC_DATA_READ)
		chan = host->dma_chan_rx;
	else
		chan = host->dma_chan_tx;
	dma_unmap_sg(chan->device->dev,
		     data->sg, data->sg_len, host->dma_dir);

	if (stat & STAT_READ_TIME_OUT)
		data->error = -ETIMEDOUT;
	else if (stat & (STAT_CRC_READ_ERROR|STAT_CRC_WRITE_ERROR))
		data->error = -EILSEQ;

	/*
	 * There appears to be a hardware design bug here.  There seems to
	 * be no way to find out how much data was transferred to the card.
	 * This means that if there was an error on any block, we mark all
	 * data blocks as being in error.
	 */
	if (!data->error)
		data->bytes_xfered = data->blocks * data->blksz;
	else
		data->bytes_xfered = 0;

	pxamci_disable_irq(host, DATA_TRAN_DONE);

	host->data = NULL;
	if (host->mrq->stop) {
		pxamci_stop_clock(host);
		pxamci_start_cmd(host, host->mrq->stop, host->cmdat);
	} else {
		pxamci_finish_request(host, host->mrq);
	}

	return 1;
}