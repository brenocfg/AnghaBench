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
struct xenbus_driver {int /*<<< orphan*/  (* is_ready ) (struct xenbus_device*) ;} ;
struct xenbus_device {scalar_t__ state; int /*<<< orphan*/  nodename; } ;
struct device_driver {int dummy; } ;
struct device {struct device_driver* driver; } ;

/* Variables and functions */
 scalar_t__ XenbusStateConnected ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct xenbus_device*) ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 
 struct xenbus_driver* to_xenbus_driver (struct device_driver*) ; 

__attribute__((used)) static int is_device_connecting(struct device *dev, void *data, bool ignore_nonessential)
{
	struct xenbus_device *xendev = to_xenbus_device(dev);
	struct device_driver *drv = data;
	struct xenbus_driver *xendrv;

	/*
	 * A device with no driver will never connect. We care only about
	 * devices which should currently be in the process of connecting.
	 */
	if (!dev->driver)
		return 0;

	/* Is this search limited to a particular driver? */
	if (drv && (dev->driver != drv))
		return 0;

	if (ignore_nonessential) {
		/* With older QEMU, for PVonHVM guests the guest config files
		 * could contain: vfb = [ 'vnc=1, vnclisten=0.0.0.0']
		 * which is nonsensical as there is no PV FB (there can be
		 * a PVKB) running as HVM guest. */

		if ((strncmp(xendev->nodename, "device/vkbd", 11) == 0))
			return 0;

		if ((strncmp(xendev->nodename, "device/vfb", 10) == 0))
			return 0;
	}
	xendrv = to_xenbus_driver(dev->driver);
	return (xendev->state < XenbusStateConnected ||
		(xendev->state == XenbusStateConnected &&
		 xendrv->is_ready && !xendrv->is_ready(xendev)));
}