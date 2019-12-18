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
struct kovaplus_info {int firmware_version; } ;
struct kovaplus_device {int /*<<< orphan*/  kovaplus_lock; } ;
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOVAPLUS_COMMAND_INFO ; 
 int /*<<< orphan*/  KOVAPLUS_SIZE_INFO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct kovaplus_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct kovaplus_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t kovaplus_sysfs_show_firmware_version(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct kovaplus_device *kovaplus;
	struct usb_device *usb_dev;
	struct kovaplus_info info;

	dev = dev->parent->parent;
	kovaplus = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = interface_to_usbdev(to_usb_interface(dev));

	mutex_lock(&kovaplus->kovaplus_lock);
	roccat_common2_receive(usb_dev, KOVAPLUS_COMMAND_INFO,
			&info, KOVAPLUS_SIZE_INFO);
	mutex_unlock(&kovaplus->kovaplus_lock);

	return snprintf(buf, PAGE_SIZE, "%d\n", info.firmware_version);
}