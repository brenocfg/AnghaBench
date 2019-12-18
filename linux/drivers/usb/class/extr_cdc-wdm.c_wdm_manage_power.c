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
struct usb_interface {int needs_remote_wakeup; } ;

/* Variables and functions */
 int usb_autopm_get_interface (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (struct usb_interface*) ; 

__attribute__((used)) static int wdm_manage_power(struct usb_interface *intf, int on)
{
	/* need autopm_get/put here to ensure the usbcore sees the new value */
	int rv = usb_autopm_get_interface(intf);

	intf->needs_remote_wakeup = on;
	if (!rv)
		usb_autopm_put_interface(intf);
	return 0;
}