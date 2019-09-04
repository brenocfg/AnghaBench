#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mv_cesa_tdma_desc {int flags; int /*<<< orphan*/  next_dma; TYPE_2__* next; } ;
struct TYPE_6__ {TYPE_2__* first; struct mv_cesa_tdma_desc* last; } ;
struct mv_cesa_req {TYPE_3__ chain; } ;
struct TYPE_4__ {struct mv_cesa_tdma_desc* last; TYPE_2__* first; } ;
struct mv_cesa_engine {TYPE_1__ chain; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  cur_dma; } ;

/* Variables and functions */
 int CESA_TDMA_BREAK_CHAIN ; 
 int CESA_TDMA_SET_STATE ; 

void mv_cesa_tdma_chain(struct mv_cesa_engine *engine,
			struct mv_cesa_req *dreq)
{
	if (engine->chain.first == NULL && engine->chain.last == NULL) {
		engine->chain.first = dreq->chain.first;
		engine->chain.last  = dreq->chain.last;
	} else {
		struct mv_cesa_tdma_desc *last;

		last = engine->chain.last;
		last->next = dreq->chain.first;
		engine->chain.last = dreq->chain.last;

		/*
		 * Break the DMA chain if the CESA_TDMA_BREAK_CHAIN is set on
		 * the last element of the current chain, or if the request
		 * being queued needs the IV regs to be set before lauching
		 * the request.
		 */
		if (!(last->flags & CESA_TDMA_BREAK_CHAIN) &&
		    !(dreq->chain.first->flags & CESA_TDMA_SET_STATE))
			last->next_dma = dreq->chain.first->cur_dma;
	}
}