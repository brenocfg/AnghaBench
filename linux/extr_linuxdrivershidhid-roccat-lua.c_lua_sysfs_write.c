#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct usb_device {int dummy; } ;
struct lua_device {int /*<<< orphan*/  lua_lock; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct lua_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int roccat_common2_send (struct usb_device*,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t lua_sysfs_write(struct file *fp, struct kobject *kobj,
		void const *buf, loff_t off, size_t count,
		size_t real_size, uint command)
{
	struct device *dev = kobj_to_dev(kobj);
	struct lua_device *lua = hid_get_drvdata(dev_get_drvdata(dev));
	struct usb_device *usb_dev = interface_to_usbdev(to_usb_interface(dev));
	int retval;

	if (off != 0 || count != real_size)
		return -EINVAL;

	mutex_lock(&lua->lua_lock);
	retval = roccat_common2_send(usb_dev, command, buf, real_size);
	mutex_unlock(&lua->lua_lock);

	return retval ? retval : real_size;
}