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
struct pch_dma_desc {int /*<<< orphan*/  desc_node; } ;
struct pch_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  active_list; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdc_dostart (struct pch_dma_chan*,struct pch_dma_desc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct pch_dma_chan* to_pd_chan (int /*<<< orphan*/ ) ; 
 struct pch_dma_desc* to_pd_desc (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t pd_tx_submit(struct dma_async_tx_descriptor *txd)
{
	struct pch_dma_desc *desc = to_pd_desc(txd);
	struct pch_dma_chan *pd_chan = to_pd_chan(txd->chan);

	spin_lock(&pd_chan->lock);

	if (list_empty(&pd_chan->active_list)) {
		list_add_tail(&desc->desc_node, &pd_chan->active_list);
		pdc_dostart(pd_chan, desc);
	} else {
		list_add_tail(&desc->desc_node, &pd_chan->queue);
	}

	spin_unlock(&pd_chan->lock);
	return 0;
}