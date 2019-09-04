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
struct ubiblock {scalar_t__ refcnt; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  list; } ;
struct ubi_volume_info {int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  devices_mutex ; 
 struct ubiblock* find_dev_nolock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ubiblock*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubiblock_cleanup (struct ubiblock*) ; 

int ubiblock_remove(struct ubi_volume_info *vi)
{
	struct ubiblock *dev;
	int ret;

	mutex_lock(&devices_mutex);
	dev = find_dev_nolock(vi->ubi_num, vi->vol_id);
	if (!dev) {
		ret = -ENODEV;
		goto out_unlock;
	}

	/* Found a device, let's lock it so we can check if it's busy */
	mutex_lock(&dev->dev_mutex);
	if (dev->refcnt > 0) {
		ret = -EBUSY;
		goto out_unlock_dev;
	}

	/* Remove from device list */
	list_del(&dev->list);
	ubiblock_cleanup(dev);
	mutex_unlock(&dev->dev_mutex);
	mutex_unlock(&devices_mutex);

	kfree(dev);
	return 0;

out_unlock_dev:
	mutex_unlock(&dev->dev_mutex);
out_unlock:
	mutex_unlock(&devices_mutex);
	return ret;
}