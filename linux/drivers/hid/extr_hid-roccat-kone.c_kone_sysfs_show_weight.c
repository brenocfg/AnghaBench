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
struct usb_device {int dummy; } ;
struct kone_device {int /*<<< orphan*/  kone_lock; } ;
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct kone_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int kone_get_weight (struct usb_device*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t kone_sysfs_show_weight(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct kone_device *kone;
	struct usb_device *usb_dev;
	int weight = 0;
	int retval;

	dev = dev->parent->parent;
	kone = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = interface_to_usbdev(to_usb_interface(dev));

	mutex_lock(&kone->kone_lock);
	retval = kone_get_weight(usb_dev, &weight);
	mutex_unlock(&kone->kone_lock);

	if (retval)
		return retval;
	return snprintf(buf, PAGE_SIZE, "%d\n", weight);
}