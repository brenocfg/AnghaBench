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
struct wusbhc {int dummy; } ;
struct wusb_dev {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct usb_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusb_dev_attr_group ; 

int wusb_dev_sysfs_add(struct wusbhc *wusbhc, struct usb_device *usb_dev,
		       struct wusb_dev *wusb_dev)
{
	int result = sysfs_create_group(&usb_dev->dev.kobj,
					&wusb_dev_attr_group);
	struct device *dev = &usb_dev->dev;
	if (result < 0)
		dev_err(dev, "Cannot register WUSB-dev attributes: %d\n",
			result);
	return result;
}