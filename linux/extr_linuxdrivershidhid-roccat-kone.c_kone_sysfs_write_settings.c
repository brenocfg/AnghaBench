#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct kone_settings {int dummy; } ;
struct TYPE_6__ {int startup_profile; } ;
struct kone_device {int /*<<< orphan*/  kone_lock; TYPE_2__ settings; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_7__ {TYPE_1__* parent; } ;
struct TYPE_5__ {struct device* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct kone_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 TYPE_4__* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  kone_profile_activated (struct kone_device*,int) ; 
 int /*<<< orphan*/  kone_profile_report (struct kone_device*,int) ; 
 int kone_set_settings (struct usb_device*,struct kone_settings const*) ; 
 int memcmp (char*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t kone_sysfs_write_settings(struct file *fp, struct kobject *kobj,
		struct bin_attribute *attr, char *buf,
		loff_t off, size_t count) {
	struct device *dev = kobj_to_dev(kobj)->parent->parent;
	struct kone_device *kone = hid_get_drvdata(dev_get_drvdata(dev));
	struct usb_device *usb_dev = interface_to_usbdev(to_usb_interface(dev));
	int retval = 0, difference, old_profile;

	/* I need to get my data in one piece */
	if (off != 0 || count != sizeof(struct kone_settings))
		return -EINVAL;

	mutex_lock(&kone->kone_lock);
	difference = memcmp(buf, &kone->settings, sizeof(struct kone_settings));
	if (difference) {
		retval = kone_set_settings(usb_dev,
				(struct kone_settings const *)buf);
		if (retval) {
			mutex_unlock(&kone->kone_lock);
			return retval;
		}

		old_profile = kone->settings.startup_profile;
		memcpy(&kone->settings, buf, sizeof(struct kone_settings));

		kone_profile_activated(kone, kone->settings.startup_profile);

		if (kone->settings.startup_profile != old_profile)
			kone_profile_report(kone, kone->settings.startup_profile);
	}
	mutex_unlock(&kone->kone_lock);

	return sizeof(struct kone_settings);
}