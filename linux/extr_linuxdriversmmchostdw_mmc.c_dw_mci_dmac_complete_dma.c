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
struct mmc_data {int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct dw_mci {scalar_t__ use_dma; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  pending_events; TYPE_2__* dma_ops; TYPE_1__* slot; int /*<<< orphan*/  dev; struct mmc_data* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup ) (struct dw_mci*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  EVENT_XFER_COMPLETE ; 
 int MMC_DATA_READ ; 
 scalar_t__ TRANS_MODE_EDMAC ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dw_mci*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_mci_dmac_complete_dma(void *arg)
{
	struct dw_mci *host = arg;
	struct mmc_data *data = host->data;

	dev_vdbg(host->dev, "DMA complete\n");

	if ((host->use_dma == TRANS_MODE_EDMAC) &&
	    data && (data->flags & MMC_DATA_READ))
		/* Invalidate cache after read */
		dma_sync_sg_for_cpu(mmc_dev(host->slot->mmc),
				    data->sg,
				    data->sg_len,
				    DMA_FROM_DEVICE);

	host->dma_ops->cleanup(host);

	/*
	 * If the card was removed, data will be NULL. No point in trying to
	 * send the stop command or waiting for NBUSY in this case.
	 */
	if (data) {
		set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
		tasklet_schedule(&host->tasklet);
	}
}