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
struct msb_data {int io_queue_stopped; int need_flush_cache; int /*<<< orphan*/  io_work; int /*<<< orphan*/  io_queue; int /*<<< orphan*/  queue; int /*<<< orphan*/  q_lock; scalar_t__ card_dead; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_start_hw_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 struct msb_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  msb_invalidate_reg_window (struct msb_data*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void msb_start(struct memstick_dev *card)
{
	struct msb_data *msb = memstick_get_drvdata(card);
	unsigned long flags;

	dbg("Resuming IO from msblock");

	msb_invalidate_reg_window(msb);

	spin_lock_irqsave(&msb->q_lock, flags);
	if (!msb->io_queue_stopped || msb->card_dead) {
		spin_unlock_irqrestore(&msb->q_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&msb->q_lock, flags);

	/* Kick cache flush anyway, its harmless */
	msb->need_flush_cache = true;
	msb->io_queue_stopped = false;

	blk_mq_start_hw_queues(msb->queue);

	queue_work(msb->io_queue, &msb->io_work);

}