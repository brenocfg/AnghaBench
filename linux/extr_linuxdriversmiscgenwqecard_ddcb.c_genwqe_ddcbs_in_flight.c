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
struct ddcb_queue {int ddcbs_in_flight; int /*<<< orphan*/  ddcb_lock; } ;
struct genwqe_dev {struct ddcb_queue queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int genwqe_ddcbs_in_flight(struct genwqe_dev *cd)
{
	unsigned long flags;
	int ddcbs_in_flight = 0;
	struct ddcb_queue *queue = &cd->queue;

	spin_lock_irqsave(&queue->ddcb_lock, flags);
	ddcbs_in_flight += queue->ddcbs_in_flight;
	spin_unlock_irqrestore(&queue->ddcb_lock, flags);

	return ddcbs_in_flight;
}