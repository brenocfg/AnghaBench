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
struct device {int /*<<< orphan*/ * driver; } ;
struct usb_interface {int /*<<< orphan*/  condition; scalar_t__ needs_remote_wakeup; scalar_t__ needs_binding; int /*<<< orphan*/  authorized; struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct usb_driver {scalar_t__ supports_autosuspend; TYPE_1__ drvwrap; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  USB_INTERFACE_BOUND ; 
 int /*<<< orphan*/  USB_INTERFACE_UNBOUND ; 
 int device_bind_driver (struct device*) ; 
 scalar_t__ device_is_registered (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (struct device*,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,void*) ; 

int usb_driver_claim_interface(struct usb_driver *driver,
				struct usb_interface *iface, void *priv)
{
	struct device *dev;
	int retval = 0;

	if (!iface)
		return -ENODEV;

	dev = &iface->dev;
	if (dev->driver)
		return -EBUSY;

	/* reject claim if interface is not authorized */
	if (!iface->authorized)
		return -ENODEV;

	dev->driver = &driver->drvwrap.driver;
	usb_set_intfdata(iface, priv);
	iface->needs_binding = 0;

	iface->condition = USB_INTERFACE_BOUND;

	/* Claimed interfaces are initially inactive (suspended) and
	 * runtime-PM-enabled, but only if the driver has autosuspend
	 * support.  Otherwise they are marked active, to prevent the
	 * device from being autosuspended, but left disabled.  In either
	 * case they are sensitive to their children's power states.
	 */
	pm_suspend_ignore_children(dev, false);
	if (driver->supports_autosuspend)
		pm_runtime_enable(dev);
	else
		pm_runtime_set_active(dev);

	/* if interface was already added, bind now; else let
	 * the future device_add() bind it, bypassing probe()
	 */
	if (device_is_registered(dev))
		retval = device_bind_driver(dev);

	if (retval) {
		dev->driver = NULL;
		usb_set_intfdata(iface, NULL);
		iface->needs_remote_wakeup = 0;
		iface->condition = USB_INTERFACE_UNBOUND;

		/*
		 * Unbound interfaces are always runtime-PM-disabled
		 * and runtime-PM-suspended
		 */
		if (driver->supports_autosuspend)
			pm_runtime_disable(dev);
		pm_runtime_set_suspended(dev);
	}

	return retval;
}