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
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;struct dma_chan* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* device_issue_pending ) (struct dma_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  stub2 (struct dma_chan*) ; 
 int /*<<< orphan*/  txd_clear_next (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txd_clear_parent (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txd_lock (struct dma_async_tx_descriptor*) ; 
 struct dma_async_tx_descriptor* txd_next (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txd_unlock (struct dma_async_tx_descriptor*) ; 

void dma_run_dependencies(struct dma_async_tx_descriptor *tx)
{
	struct dma_async_tx_descriptor *dep = txd_next(tx);
	struct dma_async_tx_descriptor *dep_next;
	struct dma_chan *chan;

	if (!dep)
		return;

	/* we'll submit tx->next now, so clear the link */
	txd_clear_next(tx);
	chan = dep->chan;

	/* keep submitting up until a channel switch is detected
	 * in that case we will be called again as a result of
	 * processing the interrupt from async_tx_channel_switch
	 */
	for (; dep; dep = dep_next) {
		txd_lock(dep);
		txd_clear_parent(dep);
		dep_next = txd_next(dep);
		if (dep_next && dep_next->chan == chan)
			txd_clear_next(dep); /* ->next will be submitted */
		else
			dep_next = NULL; /* submit current dep and terminate */
		txd_unlock(dep);

		dep->tx_submit(dep);
	}

	chan->device->device_issue_pending(chan);
}