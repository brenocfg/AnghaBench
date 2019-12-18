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
struct usb_xpad {scalar_t__ xtype; int /*<<< orphan*/  idata_dma; int /*<<< orphan*/  idata; int /*<<< orphan*/  udev; int /*<<< orphan*/  irq_in; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPAD_PKT_LEN ; 
 scalar_t__ XTYPE_XBOX360W ; 
 int /*<<< orphan*/  kfree (struct usb_xpad*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_xpad* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpad360w_stop_input (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_deinit_input (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_deinit_output (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_stop_output (struct usb_xpad*) ; 

__attribute__((used)) static void xpad_disconnect(struct usb_interface *intf)
{
	struct usb_xpad *xpad = usb_get_intfdata(intf);

	if (xpad->xtype == XTYPE_XBOX360W)
		xpad360w_stop_input(xpad);

	xpad_deinit_input(xpad);

	/*
	 * Now that both input device and LED device are gone we can
	 * stop output URB.
	 */
	xpad_stop_output(xpad);

	xpad_deinit_output(xpad);

	usb_free_urb(xpad->irq_in);
	usb_free_coherent(xpad->udev, XPAD_PKT_LEN,
			xpad->idata, xpad->idata_dma);

	kfree(xpad);

	usb_set_intfdata(intf, NULL);
}