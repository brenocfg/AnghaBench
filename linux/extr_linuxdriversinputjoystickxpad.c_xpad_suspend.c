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
struct usb_xpad {scalar_t__ xtype; scalar_t__ pad_present; struct input_dev* dev; } ;
struct usb_interface {int dummy; } ;
struct input_dev {int /*<<< orphan*/  mutex; scalar_t__ users; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 scalar_t__ XTYPE_XBOX360W ; 
 scalar_t__ auto_poweroff ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usb_xpad* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  xpad360w_poweroff_controller (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad360w_stop_input (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_stop_input (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_stop_output (struct usb_xpad*) ; 

__attribute__((used)) static int xpad_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usb_xpad *xpad = usb_get_intfdata(intf);
	struct input_dev *input = xpad->dev;

	if (xpad->xtype == XTYPE_XBOX360W) {
		/*
		 * Wireless controllers always listen to input so
		 * they are notified when controller shows up
		 * or goes away.
		 */
		xpad360w_stop_input(xpad);

		/*
		 * The wireless adapter is going off now, so the
		 * gamepads are going to become disconnected.
		 * Unless explicitly disabled, power them down
		 * so they don't just sit there flashing.
		 */
		if (auto_poweroff && xpad->pad_present)
			xpad360w_poweroff_controller(xpad);
	} else {
		mutex_lock(&input->mutex);
		if (input->users)
			xpad_stop_input(xpad);
		mutex_unlock(&input->mutex);
	}

	xpad_stop_output(xpad);

	return 0;
}