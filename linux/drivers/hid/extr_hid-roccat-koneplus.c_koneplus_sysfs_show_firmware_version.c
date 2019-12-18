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
struct koneplus_info {int firmware_version; } ;
struct koneplus_device {int /*<<< orphan*/  koneplus_lock; } ;
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  KONEPLUS_COMMAND_INFO ; 
 int /*<<< orphan*/  KONEPLUS_SIZE_INFO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct koneplus_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct koneplus_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t koneplus_sysfs_show_firmware_version(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct koneplus_device *koneplus;
	struct usb_device *usb_dev;
	struct koneplus_info info;

	dev = dev->parent->parent;
	koneplus = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = interface_to_usbdev(to_usb_interface(dev));

	mutex_lock(&koneplus->koneplus_lock);
	roccat_common2_receive(usb_dev, KONEPLUS_COMMAND_INFO,
			&info, KONEPLUS_SIZE_INFO);
	mutex_unlock(&koneplus->koneplus_lock);

	return snprintf(buf, PAGE_SIZE, "%d\n", info.firmware_version);
}