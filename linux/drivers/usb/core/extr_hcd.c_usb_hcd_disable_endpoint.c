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
struct usb_host_endpoint {int dummy; } ;
struct usb_hcd {TYPE_1__* driver; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* endpoint_disable ) (struct usb_hcd*,struct usb_host_endpoint*) ;} ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*,struct usb_host_endpoint*) ; 

void usb_hcd_disable_endpoint(struct usb_device *udev,
		struct usb_host_endpoint *ep)
{
	struct usb_hcd		*hcd;

	might_sleep();
	hcd = bus_to_hcd(udev->bus);
	if (hcd->driver->endpoint_disable)
		hcd->driver->endpoint_disable(hcd, ep);
}