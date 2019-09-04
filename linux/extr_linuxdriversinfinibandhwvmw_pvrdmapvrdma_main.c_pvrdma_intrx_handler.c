#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pvrdma_ring {int /*<<< orphan*/  cons_head; } ;
struct pvrdma_dev {int /*<<< orphan*/  cq_tbl_lock; TYPE_5__* dsr; struct pvrdma_cq** cq_tbl; TYPE_3__* pdev; TYPE_1__* cq_ring_state; } ;
struct pvrdma_cqne {size_t info; } ;
struct TYPE_12__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct pvrdma_cq {int /*<<< orphan*/  free; int /*<<< orphan*/  refcnt; TYPE_6__ ibcq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_10__ {size_t max_cq; } ;
struct TYPE_8__ {int num_pages; } ;
struct TYPE_11__ {TYPE_4__ caps; TYPE_2__ cq_ring_pages; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct pvrdma_ring rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct pvrdma_cqne* get_cqne (struct pvrdma_dev*,unsigned int) ; 
 scalar_t__ pvrdma_idx_ring_has_data (struct pvrdma_ring*,int,unsigned int*) ; 
 int /*<<< orphan*/  pvrdma_idx_ring_inc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pvrdma_intrx_handler(int irq, void *dev_id)
{
	struct pvrdma_dev *dev = dev_id;
	struct pvrdma_ring *ring = &dev->cq_ring_state->rx;
	int ring_slots = (dev->dsr->cq_ring_pages.num_pages - 1) * PAGE_SIZE /
			 sizeof(struct pvrdma_cqne);
	unsigned int head;
	unsigned long flags;

	dev_dbg(&dev->pdev->dev, "interrupt x (completion) handler\n");

	while (pvrdma_idx_ring_has_data(ring, ring_slots, &head) > 0) {
		struct pvrdma_cqne *cqne;
		struct pvrdma_cq *cq;

		cqne = get_cqne(dev, head);
		spin_lock_irqsave(&dev->cq_tbl_lock, flags);
		cq = dev->cq_tbl[cqne->info % dev->dsr->caps.max_cq];
		if (cq)
			refcount_inc(&cq->refcnt);
		spin_unlock_irqrestore(&dev->cq_tbl_lock, flags);

		if (cq && cq->ibcq.comp_handler)
			cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
		if (cq) {
			if (refcount_dec_and_test(&cq->refcnt))
				complete(&cq->free);
		}
		pvrdma_idx_ring_inc(&ring->cons_head, ring_slots);
	}

	return IRQ_HANDLED;
}