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
struct device {int dummy; } ;
struct b43legacy_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  dev_attr_interference ; 
 int /*<<< orphan*/  dev_attr_shortpreamble ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

int b43legacy_sysfs_register(struct b43legacy_wldev *wldev)
{
	struct device *dev = wldev->dev->dev;
	int err;

	B43legacy_WARN_ON(b43legacy_status(wldev) !=
			  B43legacy_STAT_INITIALIZED);

	err = device_create_file(dev, &dev_attr_interference);
	if (err)
		goto out;
	err = device_create_file(dev, &dev_attr_shortpreamble);
	if (err)
		goto err_remove_interfmode;

out:
	return err;
err_remove_interfmode:
	device_remove_file(dev, &dev_attr_interference);
	goto out;
}