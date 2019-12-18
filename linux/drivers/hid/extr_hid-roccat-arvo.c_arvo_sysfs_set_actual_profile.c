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
struct device_attribute {int dummy; } ;
struct device {TYPE_1__* parent; } ;
struct arvo_device {unsigned long actual_profile; int /*<<< orphan*/  arvo_lock; } ;
struct arvo_actual_profile {unsigned long actual_profile; int /*<<< orphan*/  command; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARVO_COMMAND_ACTUAL_PROFILE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct arvo_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int roccat_common2_send (struct usb_device*,int /*<<< orphan*/ ,struct arvo_actual_profile*,int) ; 
 int /*<<< orphan*/  to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t arvo_sysfs_set_actual_profile(struct device *dev,
		struct device_attribute *attr, char const *buf, size_t size)
{
	struct arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	struct usb_device *usb_dev =
			interface_to_usbdev(to_usb_interface(dev->parent->parent));
	struct arvo_actual_profile temp_buf;
	unsigned long profile;
	int retval;

	retval = kstrtoul(buf, 10, &profile);
	if (retval)
		return retval;

	if (profile < 1 || profile > 5)
		return -EINVAL;

	temp_buf.command = ARVO_COMMAND_ACTUAL_PROFILE;
	temp_buf.actual_profile = profile;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_send(usb_dev, ARVO_COMMAND_ACTUAL_PROFILE,
			&temp_buf, sizeof(struct arvo_actual_profile));
	if (!retval) {
		arvo->actual_profile = profile;
		retval = size;
	}
	mutex_unlock(&arvo->arvo_lock);
	return retval;
}