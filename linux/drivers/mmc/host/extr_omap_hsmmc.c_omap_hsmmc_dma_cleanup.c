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
struct omap_hsmmc_host {int dma_ch; TYPE_2__* data; scalar_t__ use_dma; int /*<<< orphan*/  irq_lock; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_5__ {int error; scalar_t__ host_cookie; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (TYPE_2__*) ; 
 struct dma_chan* omap_hsmmc_get_dma_chan (struct omap_hsmmc_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap_hsmmc_dma_cleanup(struct omap_hsmmc_host *host, int errno)
{
	int dma_ch;
	unsigned long flags;

	host->data->error = errno;

	spin_lock_irqsave(&host->irq_lock, flags);
	dma_ch = host->dma_ch;
	host->dma_ch = -1;
	spin_unlock_irqrestore(&host->irq_lock, flags);

	if (host->use_dma && dma_ch != -1) {
		struct dma_chan *chan = omap_hsmmc_get_dma_chan(host, host->data);

		dmaengine_terminate_all(chan);
		dma_unmap_sg(chan->device->dev,
			host->data->sg, host->data->sg_len,
			mmc_get_dma_dir(host->data));

		host->data->host_cookie = 0;
	}
	host->data = NULL;
}