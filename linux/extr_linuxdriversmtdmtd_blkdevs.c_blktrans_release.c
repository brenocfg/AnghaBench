#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtd_blktrans_dev {int /*<<< orphan*/  lock; scalar_t__ mtd; TYPE_1__* tr; int /*<<< orphan*/  ref; scalar_t__ open; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct mtd_blktrans_dev*) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  __put_mtd_device (scalar_t__) ; 
 struct mtd_blktrans_dev* blktrans_dev_get (struct gendisk*) ; 
 int /*<<< orphan*/  blktrans_dev_put (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  blktrans_dev_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_table_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mtd_blktrans_dev*) ; 

__attribute__((used)) static void blktrans_release(struct gendisk *disk, fmode_t mode)
{
	struct mtd_blktrans_dev *dev = blktrans_dev_get(disk);

	if (!dev)
		return;

	mutex_lock(&mtd_table_mutex);
	mutex_lock(&dev->lock);

	if (--dev->open)
		goto unlock;

	kref_put(&dev->ref, blktrans_dev_release);
	module_put(dev->tr->owner);

	if (dev->mtd) {
		if (dev->tr->release)
			dev->tr->release(dev);
		__put_mtd_device(dev->mtd);
	}
unlock:
	mutex_unlock(&dev->lock);
	mutex_unlock(&mtd_table_mutex);
	blktrans_dev_put(dev);
}