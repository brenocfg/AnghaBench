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
struct pxamci_host {int /*<<< orphan*/  lock; TYPE_1__* data; int /*<<< orphan*/  mmc; scalar_t__ base; int /*<<< orphan*/  dma_cookie; struct dma_chan* dma_chan_tx; struct dma_chan* dma_chan_rx; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_PART_FULL ; 
 int DMA_COMPLETE ; 
 int /*<<< orphan*/  EIO ; 
 int MMC_DATA_READ ; 
 scalar_t__ MMC_PRTBUF ; 
 int dmaengine_tx_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pxamci_data_done (struct pxamci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pxamci_dma_irq(void *param)
{
	struct pxamci_host *host = param;
	struct dma_tx_state state;
	enum dma_status status;
	struct dma_chan *chan;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	if (!host->data)
		goto out_unlock;

	if (host->data->flags & MMC_DATA_READ)
		chan = host->dma_chan_rx;
	else
		chan = host->dma_chan_tx;

	status = dmaengine_tx_status(chan, host->dma_cookie, &state);

	if (likely(status == DMA_COMPLETE)) {
		writel(BUF_PART_FULL, host->base + MMC_PRTBUF);
	} else {
		pr_err("%s: DMA error on %s channel\n", mmc_hostname(host->mmc),
			host->data->flags & MMC_DATA_READ ? "rx" : "tx");
		host->data->error = -EIO;
		pxamci_data_done(host, 0);
	}

out_unlock:
	spin_unlock_irqrestore(&host->lock, flags);
}