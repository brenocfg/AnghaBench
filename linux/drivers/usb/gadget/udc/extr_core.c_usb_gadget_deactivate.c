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
struct usb_gadget {int deactivated; int connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_usb_gadget_deactivate (struct usb_gadget*,int) ; 
 int usb_gadget_disconnect (struct usb_gadget*) ; 

int usb_gadget_deactivate(struct usb_gadget *gadget)
{
	int ret = 0;

	if (gadget->deactivated)
		goto out;

	if (gadget->connected) {
		ret = usb_gadget_disconnect(gadget);
		if (ret)
			goto out;

		/*
		 * If gadget was being connected before deactivation, we want
		 * to reconnect it in usb_gadget_activate().
		 */
		gadget->connected = true;
	}
	gadget->deactivated = true;

out:
	trace_usb_gadget_deactivate(gadget, ret);

	return ret;
}