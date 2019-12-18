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
struct usb_hcd {int wireless; } ;
struct usb_bus {int dummy; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (struct usb_bus*) ; 

__attribute__((used)) static unsigned usb_bus_is_wusb(struct usb_bus *bus)
{
	struct usb_hcd *hcd = bus_to_hcd(bus);
	return hcd->wireless;
}