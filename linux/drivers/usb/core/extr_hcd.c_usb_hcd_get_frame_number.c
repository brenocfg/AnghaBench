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
struct usb_device {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int (* get_frame_number ) (struct usb_hcd*) ;} ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int /*<<< orphan*/  HCD_RH_RUNNING (struct usb_hcd*) ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int stub1 (struct usb_hcd*) ; 

int usb_hcd_get_frame_number (struct usb_device *udev)
{
	struct usb_hcd	*hcd = bus_to_hcd(udev->bus);

	if (!HCD_RH_RUNNING(hcd))
		return -ESHUTDOWN;
	return hcd->driver->get_frame_number (hcd);
}