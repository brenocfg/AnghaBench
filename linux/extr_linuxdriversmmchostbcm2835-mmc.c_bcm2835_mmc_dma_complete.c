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
typedef  int /*<<< orphan*/  u32 ;
struct dma_chan {TYPE_1__* device; } ;
struct bcm2835_host {int use_dma; int wait_for_dma; int /*<<< orphan*/  lock; int /*<<< orphan*/  finish_tasklet; TYPE_2__* data; struct dma_chan* dma_chan_rxtx; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  bcm2835_mmc_finish_data (struct bcm2835_host*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_mmc_dma_complete(void *param)
{
	struct bcm2835_host *host = param;
	struct dma_chan *dma_chan;
	unsigned long flags;
	u32 dir_data;

	spin_lock_irqsave(&host->lock, flags);

	host->use_dma = false;

	if (host->data && !(host->data->flags & MMC_DATA_WRITE)) {
		/* otherwise handled in SDHCI IRQ */
		dma_chan = host->dma_chan_rxtx;
		dir_data = DMA_FROM_DEVICE;

		dma_unmap_sg(dma_chan->device->dev,
		     host->data->sg, host->data->sg_len,
		     dir_data);

		bcm2835_mmc_finish_data(host);
	} else if (host->wait_for_dma) {
		host->wait_for_dma = false;
		tasklet_schedule(&host->finish_tasklet);
	}

	spin_unlock_irqrestore(&host->lock, flags);
}