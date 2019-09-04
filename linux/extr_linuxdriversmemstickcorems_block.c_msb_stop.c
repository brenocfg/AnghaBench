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
struct msb_data {int io_queue_stopped; int /*<<< orphan*/  q_lock; int /*<<< orphan*/ * req; int /*<<< orphan*/  queue; int /*<<< orphan*/  io_queue; int /*<<< orphan*/  cache_flush_timer; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_requeue_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_stop_queue (int /*<<< orphan*/ ) ; 
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

	spin_lock_irqsave(&msb->q_lock, flags);
	blk_stop_queue(msb->queue);
	msb->io_queue_stopped = true;
	spin_unlock_irqrestore(&msb->q_lock, flags);

	del_timer_sync(&msb->cache_flush_timer);
	flush_workqueue(msb->io_queue);

	if (msb->req) {
		spin_lock_irqsave(&msb->q_lock, flags);
		blk_requeue_request(msb->queue, msb->req);
		msb->req = NULL;
		spin_unlock_irqrestore(&msb->q_lock, flags);
	}

}