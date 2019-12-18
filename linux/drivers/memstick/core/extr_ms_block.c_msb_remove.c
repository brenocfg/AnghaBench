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
struct msb_data {int card_dead; int /*<<< orphan*/  disk; int /*<<< orphan*/ * queue; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  q_lock; int /*<<< orphan*/  io_queue_stopped; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_start_hw_queues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 struct msb_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_set_drvdata (struct memstick_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msb_data_clear (struct msb_data*) ; 
 int /*<<< orphan*/  msb_disk_lock ; 
 int /*<<< orphan*/  msb_disk_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msb_stop (struct memstick_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void msb_remove(struct memstick_dev *card)
{
	struct msb_data *msb = memstick_get_drvdata(card);
	unsigned long flags;

	if (!msb->io_queue_stopped)
		msb_stop(card);

	dbg("Removing the disk device");

	/* Take care of unhandled + new requests from now on */
	spin_lock_irqsave(&msb->q_lock, flags);
	msb->card_dead = true;
	spin_unlock_irqrestore(&msb->q_lock, flags);
	blk_mq_start_hw_queues(msb->queue);

	/* Remove the disk */
	del_gendisk(msb->disk);
	blk_cleanup_queue(msb->queue);
	blk_mq_free_tag_set(&msb->tag_set);
	msb->queue = NULL;

	mutex_lock(&msb_disk_lock);
	msb_data_clear(msb);
	mutex_unlock(&msb_disk_lock);

	msb_disk_release(msb->disk);
	memstick_set_drvdata(card, NULL);
}