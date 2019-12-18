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
struct usb_device {struct device dev; } ;

/* Variables and functions */
 int add_default_authorized_attributes (struct device*) ; 
 int add_persist_attributes (struct device*) ; 
 int add_power_attributes (struct device*) ; 
 int /*<<< orphan*/  dev_bin_attr_descriptors ; 
 int device_create_bin_file (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_root_hub (struct usb_device*) ; 
 int /*<<< orphan*/  usb_remove_sysfs_dev_files (struct usb_device*) ; 

int usb_create_sysfs_dev_files(struct usb_device *udev)
{
	struct device *dev = &udev->dev;
	int retval;

	retval = device_create_bin_file(dev, &dev_bin_attr_descriptors);
	if (retval)
		goto error;

	retval = add_persist_attributes(dev);
	if (retval)
		goto error;

	retval = add_power_attributes(dev);
	if (retval)
		goto error;

	if (is_root_hub(udev)) {
		retval = add_default_authorized_attributes(dev);
		if (retval)
			goto error;
	}
	return retval;

error:
	usb_remove_sysfs_dev_files(udev);
	return retval;
}