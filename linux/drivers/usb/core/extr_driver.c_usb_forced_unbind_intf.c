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
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct usb_interface {int needs_binding; TYPE_1__ dev; } ;
struct usb_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct usb_driver* to_usb_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_release_interface (struct usb_driver*,struct usb_interface*) ; 

void usb_forced_unbind_intf(struct usb_interface *intf)
{
	struct usb_driver *driver = to_usb_driver(intf->dev.driver);

	dev_dbg(&intf->dev, "forced unbind\n");
	usb_driver_release_interface(driver, intf);

	/* Mark the interface for later rebinding */
	intf->needs_binding = 1;
}