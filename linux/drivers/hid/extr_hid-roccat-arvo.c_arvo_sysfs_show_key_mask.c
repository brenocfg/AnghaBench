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
struct arvo_key_mask {int key_mask; } ;
struct arvo_device {int /*<<< orphan*/  arvo_lock; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARVO_COMMAND_KEY_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct arvo_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,struct arvo_key_mask*,int) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t arvo_sysfs_show_key_mask(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	struct usb_device *usb_dev =
			interface_to_usbdev(to_usb_interface(dev->parent->parent));
	struct arvo_key_mask temp_buf;
	int retval;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_receive(usb_dev, ARVO_COMMAND_KEY_MASK,
			&temp_buf, sizeof(struct arvo_key_mask));
	mutex_unlock(&arvo->arvo_lock);
	if (retval)
		return retval;

	return snprintf(buf, PAGE_SIZE, "%d\n", temp_buf.key_mask);
}