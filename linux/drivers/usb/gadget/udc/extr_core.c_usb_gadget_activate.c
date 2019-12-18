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
struct usb_gadget {int deactivated; scalar_t__ connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_usb_gadget_activate (struct usb_gadget*,int) ; 
 int usb_gadget_connect (struct usb_gadget*) ; 

int usb_gadget_activate(struct usb_gadget *gadget)
{
	int ret = 0;

	if (!gadget->deactivated)
		goto out;

	gadget->deactivated = false;

	/*
	 * If gadget has been connected before deactivation, or became connected
	 * while it was being deactivated, we call usb_gadget_connect().
	 */
	if (gadget->connected)
		ret = usb_gadget_connect(gadget);

out:
	trace_usb_gadget_activate(gadget, ret);

	return ret;
}