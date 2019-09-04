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
struct rxe_cqe {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct rxe_cq {scalar_t__ notify; int /*<<< orphan*/  comp_task; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  queue; TYPE_2__ ibcq; } ;
struct TYPE_3__ {TYPE_2__* cq; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IB_CQ_NEXT_COMP ; 
 scalar_t__ IB_CQ_SOLICITED ; 
 int /*<<< orphan*/  IB_EVENT_CQ_ERR ; 
 int /*<<< orphan*/  advance_producer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct rxe_cqe*,int) ; 
 int /*<<< orphan*/  producer_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int rxe_cq_post(struct rxe_cq *cq, struct rxe_cqe *cqe, int solicited)
{
	struct ib_event ev;
	unsigned long flags;

	spin_lock_irqsave(&cq->cq_lock, flags);

	if (unlikely(queue_full(cq->queue))) {
		spin_unlock_irqrestore(&cq->cq_lock, flags);
		if (cq->ibcq.event_handler) {
			ev.device = cq->ibcq.device;
			ev.element.cq = &cq->ibcq;
			ev.event = IB_EVENT_CQ_ERR;
			cq->ibcq.event_handler(&ev, cq->ibcq.cq_context);
		}

		return -EBUSY;
	}

	memcpy(producer_addr(cq->queue), cqe, sizeof(*cqe));

	/* make sure all changes to the CQ are written before we update the
	 * producer pointer
	 */
	smp_wmb();

	advance_producer(cq->queue);
	spin_unlock_irqrestore(&cq->cq_lock, flags);

	if ((cq->notify == IB_CQ_NEXT_COMP) ||
	    (cq->notify == IB_CQ_SOLICITED && solicited)) {
		cq->notify = 0;
		tasklet_schedule(&cq->comp_task);
	}

	return 0;
}