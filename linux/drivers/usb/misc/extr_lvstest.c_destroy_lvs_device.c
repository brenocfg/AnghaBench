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
struct usb_hcd {TYPE_1__* driver; } ;
struct usb_device {int /*<<< orphan*/  bus; struct usb_device* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_dev ) (struct usb_hcd*,struct usb_device*) ;} ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void destroy_lvs_device(struct usb_device *udev)
{
	struct usb_device *hdev = udev->parent;
	struct usb_hcd *hcd = bus_to_hcd(hdev->bus);

	if (hcd->driver->free_dev)
		hcd->driver->free_dev(hcd, udev);

	usb_put_dev(udev);
}