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
struct msb_data {int io_queue_stopped; int /*<<< orphan*/  q_lock; int /*<<< orphan*/ * req; int /*<<< orphan*/  io_queue; int /*<<< orphan*/  cache_flush_timer; int /*<<< orphan*/  queue; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_requeue_request (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blk_mq_stop_hw_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct msb_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void msb_stop(struct memstick_dev *card)
{
	struct msb_data *msb = memstick_get_drvdata(card);
	unsigned long flags;

	dbg("Stopping all msblock IO");

	blk_mq_stop_hw_queues(msb->queue);
	spin_lock_irqsave(&msb->q_lock, flags);
	msb->io_queue_stopped = true;
	spin_unlock_irqrestore(&msb->q_lock, flags);

	del_timer_sync(&msb->cache_flush_timer);
	flush_workqueue(msb->io_queue);

	spin_lock_irqsave(&msb->q_lock, flags);
	if (msb->req) {
		blk_mq_requeue_request(msb->req, false);
		msb->req = NULL;
	}
	spin_unlock_irqrestore(&msb->q_lock, flags);
}