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
struct usb_xpad {int /*<<< orphan*/  irq_in; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xpad_inquiry_pad_presence (struct usb_xpad*) ; 

__attribute__((used)) static int xpad360w_start_input(struct usb_xpad *xpad)
{
	int error;

	error = usb_submit_urb(xpad->irq_in, GFP_KERNEL);
	if (error)
		return -EIO;

	/*
	 * Send presence packet.
	 * This will force the controller to resend connection packets.
	 * This is useful in the case we activate the module after the
	 * adapter has been plugged in, as it won't automatically
	 * send us info about the controllers.
	 */
	error = xpad_inquiry_pad_presence(xpad);
	if (error) {
		usb_kill_urb(xpad->irq_in);
		return error;
	}

	return 0;
}