#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  thread; } ;
struct pktcdvd_device {scalar_t__ pkt_dev; scalar_t__ refcnt; int /*<<< orphan*/  rb_pool; TYPE_2__* disk; int /*<<< orphan*/  name; int /*<<< orphan*/  bdev; TYPE_1__ cdrw; } ;
typedef  scalar_t__ dev_t ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int FMODE_NDELAY ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_WRITERS ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctl_mutex ; 
 int /*<<< orphan*/  del_gendisk (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*) ; 
 int /*<<< orphan*/  pkt_debugfs_dev_remove (struct pktcdvd_device*) ; 
 struct pktcdvd_device** pkt_devs ; 
 int /*<<< orphan*/  pkt_proc ; 
 int /*<<< orphan*/  pkt_sysfs_dev_remove (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_disk (TYPE_2__*) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkt_remove_dev(dev_t pkt_dev)
{
	struct pktcdvd_device *pd;
	int idx;
	int ret = 0;

	mutex_lock_nested(&ctl_mutex, SINGLE_DEPTH_NESTING);

	for (idx = 0; idx < MAX_WRITERS; idx++) {
		pd = pkt_devs[idx];
		if (pd && (pd->pkt_dev == pkt_dev))
			break;
	}
	if (idx == MAX_WRITERS) {
		pr_debug("dev not setup\n");
		ret = -ENXIO;
		goto out;
	}

	if (pd->refcnt > 0) {
		ret = -EBUSY;
		goto out;
	}
	if (!IS_ERR(pd->cdrw.thread))
		kthread_stop(pd->cdrw.thread);

	pkt_devs[idx] = NULL;

	pkt_debugfs_dev_remove(pd);
	pkt_sysfs_dev_remove(pd);

	blkdev_put(pd->bdev, FMODE_READ | FMODE_NDELAY);

	remove_proc_entry(pd->name, pkt_proc);
	pkt_dbg(1, pd, "writer unmapped\n");

	del_gendisk(pd->disk);
	blk_cleanup_queue(pd->disk->queue);
	put_disk(pd->disk);

	mempool_exit(&pd->rb_pool);
	kfree(pd);

	/* This is safe: open() is still holding a reference. */
	module_put(THIS_MODULE);

out:
	mutex_unlock(&ctl_mutex);
	return ret;
}