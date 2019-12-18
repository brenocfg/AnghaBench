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
struct request_queue {int dummy; } ;
struct mapped_device {int dummy; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 struct request_queue* dm_get_md_queue (struct mapped_device*) ; 
 struct mapped_device* dm_table_get_md (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_request_based (struct dm_table*) ; 

void dm_table_run_md_queue_async(struct dm_table *t)
{
	struct mapped_device *md;
	struct request_queue *queue;

	if (!dm_table_request_based(t))
		return;

	md = dm_table_get_md(t);
	queue = dm_get_md_queue(md);
	if (queue)
		blk_mq_run_hw_queues(queue, true);
}