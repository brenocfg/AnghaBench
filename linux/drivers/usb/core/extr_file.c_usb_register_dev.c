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
struct usb_interface {int minor; int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  dev; } ;
struct usb_class_driver {int minor_base; char* name; int /*<<< orphan*/ * fops; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EINVAL ; 
 int EXFULL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_USB_MINORS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MAJOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_class_driver*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int init_usb_class () ; 
 int /*<<< orphan*/  init_usb_class_mutex ; 
 int /*<<< orphan*/  kbasename (char*) ; 
 int /*<<< orphan*/  minor_rwsem ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_class ; 
 int /*<<< orphan*/ ** usb_minors ; 

int usb_register_dev(struct usb_interface *intf,
		     struct usb_class_driver *class_driver)
{
	int retval;
	int minor_base = class_driver->minor_base;
	int minor;
	char name[20];

#ifdef CONFIG_USB_DYNAMIC_MINORS
	/*
	 * We don't care what the device tries to start at, we want to start
	 * at zero to pack the devices into the smallest available space with
	 * no holes in the minor range.
	 */
	minor_base = 0;
#endif

	if (class_driver->fops == NULL)
		return -EINVAL;
	if (intf->minor >= 0)
		return -EADDRINUSE;

	mutex_lock(&init_usb_class_mutex);
	retval = init_usb_class();
	mutex_unlock(&init_usb_class_mutex);

	if (retval)
		return retval;

	dev_dbg(&intf->dev, "looking for a minor, starting at %d\n", minor_base);

	down_write(&minor_rwsem);
	for (minor = minor_base; minor < MAX_USB_MINORS; ++minor) {
		if (usb_minors[minor])
			continue;

		usb_minors[minor] = class_driver->fops;
		intf->minor = minor;
		break;
	}
	if (intf->minor < 0) {
		up_write(&minor_rwsem);
		return -EXFULL;
	}

	/* create a usb class device for this usb interface */
	snprintf(name, sizeof(name), class_driver->name, minor - minor_base);
	intf->usb_dev = device_create(usb_class->class, &intf->dev,
				      MKDEV(USB_MAJOR, minor), class_driver,
				      "%s", kbasename(name));
	if (IS_ERR(intf->usb_dev)) {
		usb_minors[minor] = NULL;
		intf->minor = -1;
		retval = PTR_ERR(intf->usb_dev);
	}
	up_write(&minor_rwsem);
	return retval;
}