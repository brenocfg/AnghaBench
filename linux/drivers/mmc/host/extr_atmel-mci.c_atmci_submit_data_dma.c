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
struct mmc_data {int dummy; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct TYPE_2__ {struct dma_async_tx_descriptor* data_desc; } ;
struct atmel_mci {TYPE_1__ dma; struct dma_chan* data_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static void
atmci_submit_data_dma(struct atmel_mci *host, struct mmc_data *data)
{
	struct dma_chan			*chan = host->data_chan;
	struct dma_async_tx_descriptor	*desc = host->dma.data_desc;

	if (chan) {
		dmaengine_submit(desc);
		dma_async_issue_pending(chan);
	}
}