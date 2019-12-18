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
struct usb_device {scalar_t__ state; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int (* enable_device ) (struct usb_hcd*,struct usb_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USB_STATE_ADDRESS ; 
 scalar_t__ USB_STATE_DEFAULT ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int stub1 (struct usb_hcd*,struct usb_device*) ; 

__attribute__((used)) static int hub_enable_device(struct usb_device *udev)
{
	struct usb_hcd *hcd = bus_to_hcd(udev->bus);

	if (!hcd->driver->enable_device)
		return 0;
	if (udev->state == USB_STATE_ADDRESS)
		return 0;
	if (udev->state != USB_STATE_DEFAULT)
		return -EINVAL;

	return hcd->driver->enable_device(hcd, udev);
}