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
struct pvrdma_qp {int qp_handle; } ;
struct pvrdma_cqe {int qp; } ;
struct TYPE_5__ {int cqe; } ;
struct pvrdma_cq {TYPE_2__ ibcq; TYPE_1__* ring_state; int /*<<< orphan*/  is_kernel; } ;
struct TYPE_6__ {int /*<<< orphan*/  cons_head; int /*<<< orphan*/  prod_tail; } ;
struct TYPE_4__ {TYPE_3__ rx; } ;

/* Variables and functions */
 struct pvrdma_cqe* get_cqe (struct pvrdma_cq*,int) ; 
 int pvrdma_idx (int /*<<< orphan*/ *,int) ; 
 int pvrdma_idx_ring_has_data (TYPE_3__*,int,unsigned int*) ; 
 int /*<<< orphan*/  pvrdma_idx_ring_inc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

void _pvrdma_flush_cqe(struct pvrdma_qp *qp, struct pvrdma_cq *cq)
{
	unsigned int head;
	int has_data;

	if (!cq->is_kernel)
		return;

	/* Lock held */
	has_data = pvrdma_idx_ring_has_data(&cq->ring_state->rx,
					    cq->ibcq.cqe, &head);
	if (unlikely(has_data > 0)) {
		int items;
		int curr;
		int tail = pvrdma_idx(&cq->ring_state->rx.prod_tail,
				      cq->ibcq.cqe);
		struct pvrdma_cqe *cqe;
		struct pvrdma_cqe *curr_cqe;

		items = (tail > head) ? (tail - head) :
			(cq->ibcq.cqe - head + tail);
		curr = --tail;
		while (items-- > 0) {
			if (curr < 0)
				curr = cq->ibcq.cqe - 1;
			if (tail < 0)
				tail = cq->ibcq.cqe - 1;
			curr_cqe = get_cqe(cq, curr);
			if ((curr_cqe->qp & 0xFFFF) != qp->qp_handle) {
				if (curr != tail) {
					cqe = get_cqe(cq, tail);
					*cqe = *curr_cqe;
				}
				tail--;
			} else {
				pvrdma_idx_ring_inc(
					&cq->ring_state->rx.cons_head,
					cq->ibcq.cqe);
			}
			curr--;
		}
	}
}