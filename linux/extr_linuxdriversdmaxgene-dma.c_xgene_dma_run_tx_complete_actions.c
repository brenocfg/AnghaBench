#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dma_async_tx_descriptor {scalar_t__ cookie; } ;
struct xgene_dma_desc_sw {struct dma_async_tx_descriptor tx; } ;
struct xgene_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_complete (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_descriptor_unmap (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgene_dma_run_tx_complete_actions(struct xgene_dma_chan *chan,
					      struct xgene_dma_desc_sw *desc)
{
	struct dma_async_tx_descriptor *tx = &desc->tx;

	/*
	 * If this is not the last transaction in the group,
	 * then no need to complete cookie and run any callback as
	 * this is not the tx_descriptor which had been sent to caller
	 * of this DMA request
	 */

	if (tx->cookie == 0)
		return;

	dma_cookie_complete(tx);
	dma_descriptor_unmap(tx);

	/* Run the link descriptor callback function */
	dmaengine_desc_get_callback_invoke(tx, NULL);

	/* Run any dependencies */
	dma_run_dependencies(tx);
}