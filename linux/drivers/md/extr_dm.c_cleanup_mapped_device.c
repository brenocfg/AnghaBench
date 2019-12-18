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
struct mapped_device {int /*<<< orphan*/  table_devices_lock; int /*<<< orphan*/  type_lock; int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  io_barrier; scalar_t__ queue; TYPE_1__* disk; int /*<<< orphan*/ * dax_dev; int /*<<< orphan*/  io_bs; int /*<<< orphan*/  bs; scalar_t__ wq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  _minor_lock ; 
 int /*<<< orphan*/  bdput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dm_mq_cleanup_mapped_device (struct mapped_device*) ; 
 int /*<<< orphan*/  kill_dax (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_dax (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_mapped_device(struct mapped_device *md)
{
	if (md->wq)
		destroy_workqueue(md->wq);
	bioset_exit(&md->bs);
	bioset_exit(&md->io_bs);

	if (md->dax_dev) {
		kill_dax(md->dax_dev);
		put_dax(md->dax_dev);
		md->dax_dev = NULL;
	}

	if (md->disk) {
		spin_lock(&_minor_lock);
		md->disk->private_data = NULL;
		spin_unlock(&_minor_lock);
		del_gendisk(md->disk);
		put_disk(md->disk);
	}

	if (md->queue)
		blk_cleanup_queue(md->queue);

	cleanup_srcu_struct(&md->io_barrier);

	if (md->bdev) {
		bdput(md->bdev);
		md->bdev = NULL;
	}

	mutex_destroy(&md->suspend_lock);
	mutex_destroy(&md->type_lock);
	mutex_destroy(&md->table_devices_lock);

	dm_mq_cleanup_mapped_device(md);
}