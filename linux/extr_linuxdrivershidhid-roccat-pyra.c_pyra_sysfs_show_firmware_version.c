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
struct pyra_info {int firmware_version; } ;
struct pyra_device {int /*<<< orphan*/  pyra_lock; } ;
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PYRA_COMMAND_INFO ; 
 int /*<<< orphan*/  PYRA_SIZE_INFO ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct pyra_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct pyra_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t pyra_sysfs_show_firmware_version(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct pyra_device *pyra;
	struct usb_device *usb_dev;
	struct pyra_info info;

	dev = dev->parent->parent;
	pyra = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = interface_to_usbdev(to_usb_interface(dev));

	mutex_lock(&pyra->pyra_lock);
	roccat_common2_receive(usb_dev, PYRA_COMMAND_INFO,
			&info, PYRA_SIZE_INFO);
	mutex_unlock(&pyra->pyra_lock);

	return snprintf(buf, PAGE_SIZE, "%d\n", info.firmware_version);
}