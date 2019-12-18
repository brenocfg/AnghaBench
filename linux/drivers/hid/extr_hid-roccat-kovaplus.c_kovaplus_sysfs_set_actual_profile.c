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
struct kovaplus_roccat_report {unsigned long profile; unsigned long data1; scalar_t__ data2; scalar_t__ button; int /*<<< orphan*/  type; } ;
struct kovaplus_device {int /*<<< orphan*/  kovaplus_lock; int /*<<< orphan*/  chrdev_minor; } ;
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROFILE_1 ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct kovaplus_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kovaplus_profile_activated (struct kovaplus_device*,unsigned long) ; 
 int kovaplus_set_actual_profile (struct usb_device*,unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t kovaplus_sysfs_set_actual_profile(struct device *dev,
		struct device_attribute *attr, char const *buf, size_t size)
{
	struct kovaplus_device *kovaplus;
	struct usb_device *usb_dev;
	unsigned long profile;
	int retval;
	struct kovaplus_roccat_report roccat_report;

	dev = dev->parent->parent;
	kovaplus = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = interface_to_usbdev(to_usb_interface(dev));

	retval = kstrtoul(buf, 10, &profile);
	if (retval)
		return retval;

	if (profile >= 5)
		return -EINVAL;

	mutex_lock(&kovaplus->kovaplus_lock);
	retval = kovaplus_set_actual_profile(usb_dev, profile);
	if (retval) {
		mutex_unlock(&kovaplus->kovaplus_lock);
		return retval;
	}

	kovaplus_profile_activated(kovaplus, profile);

	roccat_report.type = KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROFILE_1;
	roccat_report.profile = profile + 1;
	roccat_report.button = 0;
	roccat_report.data1 = profile + 1;
	roccat_report.data2 = 0;
	roccat_report_event(kovaplus->chrdev_minor,
			(uint8_t const *)&roccat_report);

	mutex_unlock(&kovaplus->kovaplus_lock);

	return size;
}