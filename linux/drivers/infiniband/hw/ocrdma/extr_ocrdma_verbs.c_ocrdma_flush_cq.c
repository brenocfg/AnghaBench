#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocrdma_dev {int dummy; } ;
struct ocrdma_cqe {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ocrdma_cq {int cqe_cnt; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  id; struct ocrdma_cqe* va; TYPE_1__ ibcq; } ;

/* Variables and functions */
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ is_cqe_valid (struct ocrdma_cq*,struct ocrdma_cqe*) ; 
 int /*<<< orphan*/  ocrdma_ring_cq_db (struct ocrdma_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ocrdma_flush_cq(struct ocrdma_cq *cq)
{
	int cqe_cnt;
	int valid_count = 0;
	unsigned long flags;

	struct ocrdma_dev *dev = get_ocrdma_dev(cq->ibcq.device);
	struct ocrdma_cqe *cqe = NULL;

	cqe = cq->va;
	cqe_cnt = cq->cqe_cnt;

	/* Last irq might have scheduled a polling thread
	 * sync-up with it before hard flushing.
	 */
	spin_lock_irqsave(&cq->cq_lock, flags);
	while (cqe_cnt) {
		if (is_cqe_valid(cq, cqe))
			valid_count++;
		cqe++;
		cqe_cnt--;
	}
	ocrdma_ring_cq_db(dev, cq->id, false, false, valid_count);
	spin_unlock_irqrestore(&cq->cq_lock, flags);
}