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
struct ddcb_queue {unsigned int ddcb_max; size_t ddcb_act; int /*<<< orphan*/  ddcb_lock; int /*<<< orphan*/  busy_waitq; int /*<<< orphan*/ * ddcb_waitqs; } ;
struct genwqe_dev {struct ddcb_queue queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int queue_wake_up_all(struct genwqe_dev *cd)
{
	unsigned int i;
	unsigned long flags;
	struct ddcb_queue *queue = &cd->queue;

	spin_lock_irqsave(&queue->ddcb_lock, flags);

	for (i = 0; i < queue->ddcb_max; i++)
		wake_up_interruptible(&queue->ddcb_waitqs[queue->ddcb_act]);

	wake_up_interruptible(&queue->busy_waitq);
	spin_unlock_irqrestore(&queue->ddcb_lock, flags);

	return 0;
}