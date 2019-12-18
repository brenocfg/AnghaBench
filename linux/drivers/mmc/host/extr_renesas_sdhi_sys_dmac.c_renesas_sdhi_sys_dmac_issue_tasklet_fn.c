#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tmio_mmc_host {int /*<<< orphan*/  lock; struct dma_chan* chan_tx; struct dma_chan* chan_rx; TYPE_1__* data; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  TMIO_STAT_DATAEND ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmio_mmc_enable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renesas_sdhi_sys_dmac_issue_tasklet_fn(unsigned long priv)
{
	struct tmio_mmc_host *host = (struct tmio_mmc_host *)priv;
	struct dma_chan *chan = NULL;

	spin_lock_irq(&host->lock);

	if (host->data) {
		if (host->data->flags & MMC_DATA_READ)
			chan = host->chan_rx;
		else
			chan = host->chan_tx;
	}

	spin_unlock_irq(&host->lock);

	tmio_mmc_enable_mmc_irqs(host, TMIO_STAT_DATAEND);

	if (chan)
		dma_async_issue_pending(chan);
}