#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns_head {TYPE_1__* disk; int /*<<< orphan*/  requeue_work; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_set_queue_dying (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 

void nvme_mpath_remove_disk(struct nvme_ns_head *head)
{
	if (!head->disk)
		return;
	if (head->disk->flags & GENHD_FL_UP)
		del_gendisk(head->disk);
	blk_set_queue_dying(head->disk->queue);
	/* make sure all pending bios are cleaned up */
	kblockd_schedule_work(&head->requeue_work);
	flush_work(&head->requeue_work);
	blk_cleanup_queue(head->disk->queue);
	put_disk(head->disk);
}