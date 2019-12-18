#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tmio_mmc_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg_ptr; TYPE_5__* chan_tx; TYPE_3__* chan_rx; TYPE_1__* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  dma_dataend; } ;
struct renesas_sdhi {TYPE_6__ dma_priv; } ;
struct TYPE_11__ {TYPE_4__* device; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_2__* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmio_mmc_do_data_irq (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void renesas_sdhi_sys_dmac_dma_callback(void *arg)
{
	struct tmio_mmc_host *host = arg;
	struct renesas_sdhi *priv = host_to_priv(host);

	spin_lock_irq(&host->lock);

	if (!host->data)
		goto out;

	if (host->data->flags & MMC_DATA_READ)
		dma_unmap_sg(host->chan_rx->device->dev,
			     host->sg_ptr, host->sg_len,
			     DMA_FROM_DEVICE);
	else
		dma_unmap_sg(host->chan_tx->device->dev,
			     host->sg_ptr, host->sg_len,
			     DMA_TO_DEVICE);

	spin_unlock_irq(&host->lock);

	wait_for_completion(&priv->dma_priv.dma_dataend);

	spin_lock_irq(&host->lock);
	tmio_mmc_do_data_irq(host);
out:
	spin_unlock_irq(&host->lock);
}