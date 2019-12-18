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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rebind_marked_interfaces (struct usb_device*) ; 
 int /*<<< orphan*/  unbind_marked_interfaces (struct usb_device*) ; 

void usb_unbind_and_rebind_marked_interfaces(struct usb_device *udev)
{
	unbind_marked_interfaces(udev);
	rebind_marked_interfaces(udev);
}