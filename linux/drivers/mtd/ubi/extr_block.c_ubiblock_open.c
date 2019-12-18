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
struct ubiblock {scalar_t__ refcnt; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/ * desc; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; int /*<<< orphan*/  gd; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int fmode_t ;
struct TYPE_2__ {struct ubiblock* private_data; } ;

/* Variables and functions */
 int EROFS ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UBI_READONLY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ubi_open_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ubiblock_open(struct block_device *bdev, fmode_t mode)
{
	struct ubiblock *dev = bdev->bd_disk->private_data;
	int ret;

	mutex_lock(&dev->dev_mutex);
	if (dev->refcnt > 0) {
		/*
		 * The volume is already open, just increase the reference
		 * counter.
		 */
		goto out_done;
	}

	/*
	 * We want users to be aware they should only mount us as read-only.
	 * It's just a paranoid check, as write requests will get rejected
	 * in any case.
	 */
	if (mode & FMODE_WRITE) {
		ret = -EROFS;
		goto out_unlock;
	}

	dev->desc = ubi_open_volume(dev->ubi_num, dev->vol_id, UBI_READONLY);
	if (IS_ERR(dev->desc)) {
		dev_err(disk_to_dev(dev->gd), "failed to open ubi volume %d_%d",
			dev->ubi_num, dev->vol_id);
		ret = PTR_ERR(dev->desc);
		dev->desc = NULL;
		goto out_unlock;
	}

out_done:
	dev->refcnt++;
	mutex_unlock(&dev->dev_mutex);
	return 0;

out_unlock:
	mutex_unlock(&dev->dev_mutex);
	return ret;
}