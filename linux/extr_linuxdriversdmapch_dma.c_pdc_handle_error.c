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
struct TYPE_3__ {int /*<<< orphan*/  cookie; } ;
struct pch_dma_desc {TYPE_1__ txd; int /*<<< orphan*/  desc_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  prev; } ;
struct pch_dma_chan {int /*<<< orphan*/  chan; TYPE_2__ active_list; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_chain_complete (struct pch_dma_chan*,struct pch_dma_desc*) ; 
 int /*<<< orphan*/  pdc_dostart (struct pch_dma_chan*,struct pch_dma_desc*) ; 
 struct pch_dma_desc* pdc_first_active (struct pch_dma_chan*) ; 

__attribute__((used)) static void pdc_handle_error(struct pch_dma_chan *pd_chan)
{
	struct pch_dma_desc *bad_desc;

	bad_desc = pdc_first_active(pd_chan);
	list_del(&bad_desc->desc_node);

	list_splice_init(&pd_chan->queue, pd_chan->active_list.prev);

	if (!list_empty(&pd_chan->active_list))
		pdc_dostart(pd_chan, pdc_first_active(pd_chan));

	dev_crit(chan2dev(&pd_chan->chan), "Bad descriptor submitted\n");
	dev_crit(chan2dev(&pd_chan->chan), "descriptor cookie: %d\n",
		 bad_desc->txd.cookie);

	pdc_chain_complete(pd_chan, bad_desc);
}