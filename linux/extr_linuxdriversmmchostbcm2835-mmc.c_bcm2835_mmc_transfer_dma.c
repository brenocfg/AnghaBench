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
typedef  scalar_t__ u32 ;
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {struct bcm2835_host* callback_param; int /*<<< orphan*/  callback; } ;
struct bcm2835_host {scalar_t__ blocks; int /*<<< orphan*/  lock; struct dma_async_tx_descriptor* tx_desc; int /*<<< orphan*/  mmc; TYPE_2__* data; int /*<<< orphan*/  dma_cfg_tx; int /*<<< orphan*/  dma_cfg_rx; struct dma_chan* dma_chan_rxtx; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  sg; int /*<<< orphan*/  sg_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_CTRL_ACK ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int MMC_DATA_READ ; 
 int SDHCI_INT_DATA_AVAIL ; 
 int SDHCI_INT_SPACE_AVAIL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bcm2835_mmc_dma_complete ; 
 int /*<<< orphan*/  bcm2835_mmc_unsignal_irqs (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 scalar_t__ dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  dmaengine_slave_config (struct dma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_mmc_transfer_dma(struct bcm2835_host *host)
{
	u32 len, dir_data, dir_slave;
	struct dma_async_tx_descriptor *desc = NULL;
	struct dma_chan *dma_chan;


	WARN_ON(!host->data);

	if (!host->data)
		return;

	if (host->blocks == 0)
		return;

	dma_chan = host->dma_chan_rxtx;
	if (host->data->flags & MMC_DATA_READ) {
		dir_data = DMA_FROM_DEVICE;
		dir_slave = DMA_DEV_TO_MEM;
	} else {
		dir_data = DMA_TO_DEVICE;
		dir_slave = DMA_MEM_TO_DEV;
	}

	/* The parameters have already been validated, so this will not fail */
	(void)dmaengine_slave_config(dma_chan,
				     (dir_data == DMA_FROM_DEVICE) ?
				     &host->dma_cfg_rx :
				     &host->dma_cfg_tx);

	BUG_ON(!dma_chan->device);
	BUG_ON(!dma_chan->device->dev);
	BUG_ON(!host->data->sg);

	len = dma_map_sg(dma_chan->device->dev, host->data->sg,
			 host->data->sg_len, dir_data);
	if (len > 0) {
		desc = dmaengine_prep_slave_sg(dma_chan, host->data->sg,
					       len, dir_slave,
					       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	} else {
		dev_err(mmc_dev(host->mmc), "dma_map_sg returned zero length\n");
	}
	if (desc) {
		unsigned long flags;
		spin_lock_irqsave(&host->lock, flags);
		bcm2835_mmc_unsignal_irqs(host, SDHCI_INT_DATA_AVAIL |
						    SDHCI_INT_SPACE_AVAIL);
		host->tx_desc = desc;
		desc->callback = bcm2835_mmc_dma_complete;
		desc->callback_param = host;
		spin_unlock_irqrestore(&host->lock, flags);
		dmaengine_submit(desc);
		dma_async_issue_pending(dma_chan);
	}

}