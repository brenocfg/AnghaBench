#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtd_blktrans_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/ * mtd; TYPE_1__* tr; scalar_t__ open; int /*<<< orphan*/  queue_lock; TYPE_3__* rq; int /*<<< orphan*/  wq; int /*<<< orphan*/  disk; scalar_t__ disk_attributes; } ;
struct TYPE_6__ {int /*<<< orphan*/ * queuedata; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release ) (struct mtd_blktrans_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  __put_mtd_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_start_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  blktrans_dev_put (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 TYPE_2__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_table_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,scalar_t__) ; 

int del_mtd_blktrans_dev(struct mtd_blktrans_dev *old)
{
	unsigned long flags;

	if (mutex_trylock(&mtd_table_mutex)) {
		mutex_unlock(&mtd_table_mutex);
		BUG();
	}

	if (old->disk_attributes)
		sysfs_remove_group(&disk_to_dev(old->disk)->kobj,
						old->disk_attributes);

	/* Stop new requests to arrive */
	del_gendisk(old->disk);

	/* Stop workqueue. This will perform any pending request. */
	destroy_workqueue(old->wq);

	/* Kill current requests */
	spin_lock_irqsave(&old->queue_lock, flags);
	old->rq->queuedata = NULL;
	blk_start_queue(old->rq);
	spin_unlock_irqrestore(&old->queue_lock, flags);

	/* If the device is currently open, tell trans driver to close it,
		then put mtd device, and don't touch it again */
	mutex_lock(&old->lock);
	if (old->open) {
		if (old->tr->release)
			old->tr->release(old);
		__put_mtd_device(old->mtd);
	}

	old->mtd = NULL;

	mutex_unlock(&old->lock);
	blktrans_dev_put(old);
	return 0;
}