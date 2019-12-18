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
typedef  int u16 ;
struct sdma_txreq {int next_descq_idx; } ;
struct sdma_engine {int descq_head; int sdma_mask; int descq_tail; int /*<<< orphan*/  tx_head; int /*<<< orphan*/ ** tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_TXREQ_S_ABORTED ; 
 int /*<<< orphan*/  complete_tx (struct sdma_engine*,struct sdma_txreq*,int /*<<< orphan*/ ) ; 
 struct sdma_txreq* get_txhead (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_desc_avail (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_descq_freecnt (struct sdma_engine*) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_progress (struct sdma_engine*,int,int,struct sdma_txreq*) ; 

__attribute__((used)) static void sdma_flush_descq(struct sdma_engine *sde)
{
	u16 head, tail;
	int progress = 0;
	struct sdma_txreq *txp = get_txhead(sde);

	/* The reason for some of the complexity of this code is that
	 * not all descriptors have corresponding txps.  So, we have to
	 * be able to skip over descs until we wander into the range of
	 * the next txp on the list.
	 */
	head = sde->descq_head & sde->sdma_mask;
	tail = sde->descq_tail & sde->sdma_mask;
	while (head != tail) {
		/* advance head, wrap if needed */
		head = ++sde->descq_head & sde->sdma_mask;
		/* if now past this txp's descs, do the callback */
		if (txp && txp->next_descq_idx == head) {
			/* remove from list */
			sde->tx_ring[sde->tx_head++ & sde->sdma_mask] = NULL;
			complete_tx(sde, txp, SDMA_TXREQ_S_ABORTED);
			trace_hfi1_sdma_progress(sde, head, tail, txp);
			txp = get_txhead(sde);
		}
		progress++;
	}
	if (progress)
		sdma_desc_avail(sde, sdma_descq_freecnt(sde));
}