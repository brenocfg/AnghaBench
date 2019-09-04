#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_device {int dummy; } ;
struct pyra_settings {scalar_t__ startup_profile; } ;
struct pyra_roccat_report {scalar_t__ value; scalar_t__ key; int /*<<< orphan*/  type; } ;
struct pyra_device {int /*<<< orphan*/  pyra_lock; int /*<<< orphan*/  chrdev_minor; int /*<<< orphan*/  profile_settings; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct TYPE_3__ {struct device* parent; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PYRA_MOUSE_EVENT_BUTTON_TYPE_PROFILE_2 ; 
 size_t PYRA_SIZE_SETTINGS ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct pyra_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 TYPE_2__* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_activated (struct pyra_device*,scalar_t__) ; 
 int pyra_set_settings (struct usb_device*,struct pyra_settings const*) ; 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t pyra_sysfs_write_settings(struct file *fp,
		struct kobject *kobj, struct bin_attribute *attr, char *buf,
		loff_t off, size_t count)
{
	struct device *dev = kobj_to_dev(kobj)->parent->parent;
	struct pyra_device *pyra = hid_get_drvdata(dev_get_drvdata(dev));
	struct usb_device *usb_dev = interface_to_usbdev(to_usb_interface(dev));
	int retval = 0;
	struct pyra_roccat_report roccat_report;
	struct pyra_settings const *settings;

	if (off != 0 || count != PYRA_SIZE_SETTINGS)
		return -EINVAL;

	settings = (struct pyra_settings const *)buf;
	if (settings->startup_profile >= ARRAY_SIZE(pyra->profile_settings))
		return -EINVAL;

	mutex_lock(&pyra->pyra_lock);

	retval = pyra_set_settings(usb_dev, settings);
	if (retval) {
		mutex_unlock(&pyra->pyra_lock);
		return retval;
	}

	profile_activated(pyra, settings->startup_profile);

	roccat_report.type = PYRA_MOUSE_EVENT_BUTTON_TYPE_PROFILE_2;
	roccat_report.value = settings->startup_profile + 1;
	roccat_report.key = 0;
	roccat_report_event(pyra->chrdev_minor,
			(uint8_t const *)&roccat_report);

	mutex_unlock(&pyra->pyra_lock);
	return PYRA_SIZE_SETTINGS;
}