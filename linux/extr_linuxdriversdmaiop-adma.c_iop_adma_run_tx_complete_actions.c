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
struct iop_adma_desc_slot {int /*<<< orphan*/ * group_head; struct dma_async_tx_descriptor async_tx; } ;
struct iop_adma_chan {int dummy; } ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_descriptor_unmap (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static dma_cookie_t
iop_adma_run_tx_complete_actions(struct iop_adma_desc_slot *desc,
	struct iop_adma_chan *iop_chan, dma_cookie_t cookie)
{
	struct dma_async_tx_descriptor *tx = &desc->async_tx;

	BUG_ON(tx->cookie < 0);
	if (tx->cookie > 0) {
		cookie = tx->cookie;
		tx->cookie = 0;

		/* call the callback (must not sleep or submit new
		 * operations to this channel)
		 */
		dmaengine_desc_get_callback_invoke(tx, NULL);

		dma_descriptor_unmap(tx);
		if (desc->group_head)
			desc->group_head = NULL;
	}

	/* run dependent operations */
	dma_run_dependencies(tx);

	return cookie;
}