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
typedef  size_t uint ;
struct usb_device {int dummy; } ;
struct kone_profile {int dummy; } ;
struct kone_device {int /*<<< orphan*/  kone_lock; struct kone_profile* profiles; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {scalar_t__ private; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct TYPE_3__ {struct device* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct kone_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 TYPE_2__* kobj_to_dev (struct kobject*) ; 
 int kone_set_profile (struct usb_device*,struct kone_profile const*,size_t) ; 
 int memcmp (char*,struct kone_profile*,int) ; 
 int /*<<< orphan*/  memcpy (struct kone_profile*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t kone_sysfs_write_profilex(struct file *fp,
		struct kobject *kobj, struct bin_attribute *attr,
		char *buf, loff_t off, size_t count) {
	struct device *dev = kobj_to_dev(kobj)->parent->parent;
	struct kone_device *kone = hid_get_drvdata(dev_get_drvdata(dev));
	struct usb_device *usb_dev = interface_to_usbdev(to_usb_interface(dev));
	struct kone_profile *profile;
	int retval = 0, difference;

	/* I need to get my data in one piece */
	if (off != 0 || count != sizeof(struct kone_profile))
		return -EINVAL;

	profile = &kone->profiles[*(uint *)(attr->private)];

	mutex_lock(&kone->kone_lock);
	difference = memcmp(buf, profile, sizeof(struct kone_profile));
	if (difference) {
		retval = kone_set_profile(usb_dev,
				(struct kone_profile const *)buf,
				*(uint *)(attr->private) + 1);
		if (!retval)
			memcpy(profile, buf, sizeof(struct kone_profile));
	}
	mutex_unlock(&kone->kone_lock);

	if (retval)
		return retval;

	return sizeof(struct kone_profile);
}