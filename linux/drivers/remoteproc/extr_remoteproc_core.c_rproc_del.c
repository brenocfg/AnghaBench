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
struct rproc {int /*<<< orphan*/  dev; int /*<<< orphan*/  node; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; scalar_t__ auto_boot; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RPROC_DELETED ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_delete_debug_dir (struct rproc*) ; 
 int /*<<< orphan*/  rproc_list_mutex ; 
 int /*<<< orphan*/  rproc_shutdown (struct rproc*) ; 

int rproc_del(struct rproc *rproc)
{
	if (!rproc)
		return -EINVAL;

	/* if rproc is marked always-on, rproc_add() booted it */
	/* TODO: make sure this works with rproc->power > 1 */
	if (rproc->auto_boot)
		rproc_shutdown(rproc);

	mutex_lock(&rproc->lock);
	rproc->state = RPROC_DELETED;
	mutex_unlock(&rproc->lock);

	rproc_delete_debug_dir(rproc);

	/* the rproc is downref'ed as soon as it's removed from the klist */
	mutex_lock(&rproc_list_mutex);
	list_del(&rproc->node);
	mutex_unlock(&rproc_list_mutex);

	device_del(&rproc->dev);

	return 0;
}