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
struct rxe_cqe {int /*<<< orphan*/  ibwc; } ;
struct rxe_cq {int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  queue; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_consumer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct rxe_cqe* queue_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rxe_cq* to_rcq (struct ib_cq*) ; 

__attribute__((used)) static int rxe_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	int i;
	struct rxe_cq *cq = to_rcq(ibcq);
	struct rxe_cqe *cqe;
	unsigned long flags;

	spin_lock_irqsave(&cq->cq_lock, flags);
	for (i = 0; i < num_entries; i++) {
		cqe = queue_head(cq->queue);
		if (!cqe)
			break;

		memcpy(wc++, &cqe->ibwc, sizeof(*wc));
		advance_consumer(cq->queue);
	}
	spin_unlock_irqrestore(&cq->cq_lock, flags);

	return i;
}