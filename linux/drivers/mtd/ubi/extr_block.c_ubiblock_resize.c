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
typedef  scalar_t__ u64 ;
struct ubiblock {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  gd; } ;
struct ubi_volume_info {int /*<<< orphan*/  used_bytes; int /*<<< orphan*/  size; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;

/* Variables and functions */
 int EFBIG ; 
 int ENODEV ; 
 int calc_disk_capacity (struct ubi_volume_info*,scalar_t__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devices_mutex ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 struct ubiblock* find_dev_nolock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ubiblock_resize(struct ubi_volume_info *vi)
{
	struct ubiblock *dev;
	u64 disk_capacity;
	int ret;

	/*
	 * Need to lock the device list until we stop using the device,
	 * otherwise the device struct might get released in
	 * 'ubiblock_remove()'.
	 */
	mutex_lock(&devices_mutex);
	dev = find_dev_nolock(vi->ubi_num, vi->vol_id);
	if (!dev) {
		mutex_unlock(&devices_mutex);
		return -ENODEV;
	}

	ret = calc_disk_capacity(vi, &disk_capacity);
	if (ret) {
		mutex_unlock(&devices_mutex);
		if (ret == -EFBIG) {
			dev_warn(disk_to_dev(dev->gd),
				 "the volume is too big (%d LEBs), cannot resize",
				 vi->size);
		}
		return ret;
	}

	mutex_lock(&dev->dev_mutex);

	if (get_capacity(dev->gd) != disk_capacity) {
		set_capacity(dev->gd, disk_capacity);
		dev_info(disk_to_dev(dev->gd), "resized to %lld bytes",
			 vi->used_bytes);
	}
	mutex_unlock(&dev->dev_mutex);
	mutex_unlock(&devices_mutex);
	return 0;
}