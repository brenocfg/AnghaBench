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
struct device {int dummy; } ;
struct rproc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * table_ptr; int /*<<< orphan*/ * cached_table; int /*<<< orphan*/  power; int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_disable_iommu (struct rproc*) ; 
 int /*<<< orphan*/  rproc_resource_cleanup (struct rproc*) ; 
 int rproc_stop (struct rproc*,int) ; 

void rproc_shutdown(struct rproc *rproc)
{
	struct device *dev = &rproc->dev;
	int ret;

	ret = mutex_lock_interruptible(&rproc->lock);
	if (ret) {
		dev_err(dev, "can't lock rproc %s: %d\n", rproc->name, ret);
		return;
	}

	/* if the remote proc is still needed, bail out */
	if (!atomic_dec_and_test(&rproc->power))
		goto out;

	ret = rproc_stop(rproc, false);
	if (ret) {
		atomic_inc(&rproc->power);
		goto out;
	}

	/* clean up all acquired resources */
	rproc_resource_cleanup(rproc);

	rproc_disable_iommu(rproc);

	/* Free the copy of the resource table */
	kfree(rproc->cached_table);
	rproc->cached_table = NULL;
	rproc->table_ptr = NULL;
out:
	mutex_unlock(&rproc->lock);
}