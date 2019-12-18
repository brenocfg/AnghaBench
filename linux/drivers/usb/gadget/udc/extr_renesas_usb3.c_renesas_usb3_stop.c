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
struct usb_gadget {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct renesas_usb3 {int softconnect; scalar_t__ phy; int /*<<< orphan*/ * driver; TYPE_1__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 struct renesas_usb3* gadget_to_renesas_usb3 (struct usb_gadget*) ; 
 int /*<<< orphan*/  phy_exit (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  renesas_usb3_stop_controller (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_to_dev (struct renesas_usb3*) ; 

__attribute__((used)) static int renesas_usb3_stop(struct usb_gadget *gadget)
{
	struct renesas_usb3 *usb3 = gadget_to_renesas_usb3(gadget);

	usb3->softconnect = false;
	usb3->gadget.speed = USB_SPEED_UNKNOWN;
	usb3->driver = NULL;
	renesas_usb3_stop_controller(usb3);

	if (usb3->phy)
		phy_exit(usb3->phy);

	pm_runtime_put(usb3_to_dev(usb3));

	return 0;
}