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
struct usb_port {int quirks; } ;
struct usb_device {scalar_t__ speed; } ;

/* Variables and functions */
 int USB_PORT_QUIRK_OLD_SCHEME ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int USE_NEW_SCHEME (int,int) ; 
 scalar_t__ old_scheme_first ; 

__attribute__((used)) static bool use_new_scheme(struct usb_device *udev, int retry,
			   struct usb_port *port_dev)
{
	int old_scheme_first_port =
		port_dev->quirks & USB_PORT_QUIRK_OLD_SCHEME;
	int quick_enumeration = (udev->speed == USB_SPEED_HIGH);

	if (udev->speed >= USB_SPEED_SUPER)
		return false;

	return USE_NEW_SCHEME(retry, old_scheme_first_port || old_scheme_first
			      || quick_enumeration);
}