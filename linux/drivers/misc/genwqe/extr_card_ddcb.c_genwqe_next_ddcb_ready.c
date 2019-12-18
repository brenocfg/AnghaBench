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
struct ddcb_queue {size_t ddcb_act; int /*<<< orphan*/  ddcb_lock; struct ddcb* ddcb_vaddr; } ;
struct genwqe_dev {struct ddcb_queue queue; } ;
struct ddcb {int icrc_hsi_shi_32; } ;

/* Variables and functions */
 int DDCB_COMPLETED_BE32 ; 
 scalar_t__ queue_empty (struct ddcb_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int genwqe_next_ddcb_ready(struct genwqe_dev *cd)
{
	unsigned long flags;
	struct ddcb *pddcb;
	struct ddcb_queue *queue = &cd->queue;

	spin_lock_irqsave(&queue->ddcb_lock, flags);

	if (queue_empty(queue)) { /* emtpy queue */
		spin_unlock_irqrestore(&queue->ddcb_lock, flags);
		return 0;
	}

	pddcb = &queue->ddcb_vaddr[queue->ddcb_act];
	if (pddcb->icrc_hsi_shi_32 & DDCB_COMPLETED_BE32) { /* ddcb ready */
		spin_unlock_irqrestore(&queue->ddcb_lock, flags);
		return 1;
	}

	spin_unlock_irqrestore(&queue->ddcb_lock, flags);
	return 0;
}