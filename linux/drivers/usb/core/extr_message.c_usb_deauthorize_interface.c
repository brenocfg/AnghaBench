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
struct device {struct device* parent; } ;
struct usb_interface {scalar_t__ authorized; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  usb_forced_unbind_intf (struct usb_interface*) ; 

void usb_deauthorize_interface(struct usb_interface *intf)
{
	struct device *dev = &intf->dev;

	device_lock(dev->parent);

	if (intf->authorized) {
		device_lock(dev);
		intf->authorized = 0;
		device_unlock(dev);

		usb_forced_unbind_intf(intf);
	}

	device_unlock(dev->parent);
}