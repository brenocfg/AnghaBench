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
struct rbd_device {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  task_wq; int /*<<< orphan*/  opts; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct rbd_device* dev_to_rbd_dev (struct device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_dev_free (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_dev_id_ida ; 

__attribute__((used)) static void rbd_dev_release(struct device *dev)
{
	struct rbd_device *rbd_dev = dev_to_rbd_dev(dev);
	bool need_put = !!rbd_dev->opts;

	if (need_put) {
		destroy_workqueue(rbd_dev->task_wq);
		ida_simple_remove(&rbd_dev_id_ida, rbd_dev->dev_id);
	}

	rbd_dev_free(rbd_dev);

	/*
	 * This is racy, but way better than putting module outside of
	 * the release callback.  The race window is pretty small, so
	 * doing something similar to dm (dm-builtin.c) is overkill.
	 */
	if (need_put)
		module_put(THIS_MODULE);
}