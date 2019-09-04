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
struct ibmvmc_crq_msg {int valid; } ;
struct crq_queue {size_t cur; size_t size; int /*<<< orphan*/  lock; struct ibmvmc_crq_msg* msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct ibmvmc_crq_msg *crq_queue_next_crq(struct crq_queue *queue)
{
	struct ibmvmc_crq_msg *crq;
	unsigned long flags;

	spin_lock_irqsave(&queue->lock, flags);
	crq = &queue->msgs[queue->cur];
	if (crq->valid & 0x80) {
		if (++queue->cur == queue->size)
			queue->cur = 0;

		/* Ensure the read of the valid bit occurs before reading any
		 * other bits of the CRQ entry
		 */
		dma_rmb();
	} else {
		crq = NULL;
	}

	spin_unlock_irqrestore(&queue->lock, flags);

	return crq;
}