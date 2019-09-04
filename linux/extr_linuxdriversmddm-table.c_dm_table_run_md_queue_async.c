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
struct request_queue {int /*<<< orphan*/  queue_lock; scalar_t__ mq_ops; } ;
struct mapped_device {int dummy; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_run_queue_async (struct request_queue*) ; 
 struct request_queue* dm_get_md_queue (struct mapped_device*) ; 
 struct mapped_device* dm_table_get_md (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_request_based (struct dm_table*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void dm_table_run_md_queue_async(struct dm_table *t)
{
	struct mapped_device *md;
	struct request_queue *queue;
	unsigned long flags;

	if (!dm_table_request_based(t))
		return;

	md = dm_table_get_md(t);
	queue = dm_get_md_queue(md);
	if (queue) {
		if (queue->mq_ops)
			blk_mq_run_hw_queues(queue, true);
		else {
			spin_lock_irqsave(queue->queue_lock, flags);
			blk_run_queue_async(queue);
			spin_unlock_irqrestore(queue->queue_lock, flags);
		}
	}
}