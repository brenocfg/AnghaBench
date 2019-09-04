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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_device {int dummy; } ;
struct isku_roccat_report {unsigned long data1; unsigned long profile; scalar_t__ data2; int /*<<< orphan*/  event; } ;
struct isku_device {int /*<<< orphan*/  isku_lock; int /*<<< orphan*/  chrdev_minor; } ;
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISKU_REPORT_BUTTON_EVENT_PROFILE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct isku_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isku_profile_activated (struct isku_device*,unsigned long) ; 
 int isku_set_actual_profile (struct usb_device*,unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t isku_sysfs_set_actual_profile(struct device *dev,
		struct device_attribute *attr, char const *buf, size_t size)
{
	struct isku_device *isku;
	struct usb_device *usb_dev;
	unsigned long profile;
	int retval;
	struct isku_roccat_report roccat_report;

	dev = dev->parent->parent;
	isku = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = interface_to_usbdev(to_usb_interface(dev));

	retval = kstrtoul(buf, 10, &profile);
	if (retval)
		return retval;

	if (profile > 4)
		return -EINVAL;

	mutex_lock(&isku->isku_lock);

	retval = isku_set_actual_profile(usb_dev, profile);
	if (retval) {
		mutex_unlock(&isku->isku_lock);
		return retval;
	}

	isku_profile_activated(isku, profile);

	roccat_report.event = ISKU_REPORT_BUTTON_EVENT_PROFILE;
	roccat_report.data1 = profile + 1;
	roccat_report.data2 = 0;
	roccat_report.profile = profile + 1;
	roccat_report_event(isku->chrdev_minor, (uint8_t const *)&roccat_report);

	mutex_unlock(&isku->isku_lock);

	return size;
}