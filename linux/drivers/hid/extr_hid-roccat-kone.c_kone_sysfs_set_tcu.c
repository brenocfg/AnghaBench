#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {unsigned long tcu; int /*<<< orphan*/  startup_profile; } ;
struct kone_device {int /*<<< orphan*/  kone_lock; TYPE_2__ settings; } ;
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
typedef  int ssize_t ;
struct TYPE_5__ {struct device* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct kone_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int kone_get_settings (struct usb_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  kone_profile_activated (struct kone_device*,int /*<<< orphan*/ ) ; 
 int kone_set_settings (struct usb_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  kone_set_settings_checksum (TYPE_2__*) ; 
 int kone_tcu_command (struct usb_device*,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t kone_sysfs_set_tcu(struct device *dev,
		struct device_attribute *attr, char const *buf, size_t size)
{
	struct kone_device *kone;
	struct usb_device *usb_dev;
	int retval;
	unsigned long state;

	dev = dev->parent->parent;
	kone = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = interface_to_usbdev(to_usb_interface(dev));

	retval = kstrtoul(buf, 10, &state);
	if (retval)
		return retval;

	if (state != 0 && state != 1)
		return -EINVAL;

	mutex_lock(&kone->kone_lock);

	if (state == 1) { /* state activate */
		retval = kone_tcu_command(usb_dev, 1);
		if (retval)
			goto exit_unlock;
		retval = kone_tcu_command(usb_dev, 2);
		if (retval)
			goto exit_unlock;
		ssleep(5); /* tcu needs this time for calibration */
		retval = kone_tcu_command(usb_dev, 3);
		if (retval)
			goto exit_unlock;
		retval = kone_tcu_command(usb_dev, 0);
		if (retval)
			goto exit_unlock;
		retval = kone_tcu_command(usb_dev, 4);
		if (retval)
			goto exit_unlock;
		/*
		 * Kone needs this time to settle things.
		 * Reading settings too early will result in invalid data.
		 * Roccat's driver waits 1 sec, maybe this time could be
		 * shortened.
		 */
		ssleep(1);
	}

	/* calibration changes values in settings, so reread */
	retval = kone_get_settings(usb_dev, &kone->settings);
	if (retval)
		goto exit_no_settings;

	/* only write settings back if activation state is different */
	if (kone->settings.tcu != state) {
		kone->settings.tcu = state;
		kone_set_settings_checksum(&kone->settings);

		retval = kone_set_settings(usb_dev, &kone->settings);
		if (retval) {
			dev_err(&usb_dev->dev, "couldn't set tcu state\n");
			/*
			 * try to reread valid settings into buffer overwriting
			 * first error code
			 */
			retval = kone_get_settings(usb_dev, &kone->settings);
			if (retval)
				goto exit_no_settings;
			goto exit_unlock;
		}
		/* calibration resets profile */
		kone_profile_activated(kone, kone->settings.startup_profile);
	}

	retval = size;
exit_no_settings:
	dev_err(&usb_dev->dev, "couldn't read settings\n");
exit_unlock:
	mutex_unlock(&kone->kone_lock);
	return retval;
}