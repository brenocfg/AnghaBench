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
struct mdev_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_is_mdev (struct device*) ; 
 int /*<<< orphan*/  mdev_device_remove_common (struct mdev_device*) ; 
 struct mdev_device* to_mdev_device (struct device*) ; 

__attribute__((used)) static int mdev_device_remove_cb(struct device *dev, void *data)
{
	if (dev_is_mdev(dev)) {
		struct mdev_device *mdev;

		mdev = to_mdev_device(dev);
		mdev_device_remove_common(mdev);
	}
	return 0;
}