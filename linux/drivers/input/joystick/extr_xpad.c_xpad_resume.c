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
struct usb_xpad {scalar_t__ xtype; struct input_dev* dev; } ;
struct usb_interface {int dummy; } ;
struct input_dev {int /*<<< orphan*/  mutex; scalar_t__ users; } ;

/* Variables and functions */
 scalar_t__ XTYPE_XBOX360W ; 
 scalar_t__ XTYPE_XBOXONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usb_xpad* usb_get_intfdata (struct usb_interface*) ; 
 int xpad360w_start_input (struct usb_xpad*) ; 
 int xpad_start_input (struct usb_xpad*) ; 
 int xpad_start_xbox_one (struct usb_xpad*) ; 

__attribute__((used)) static int xpad_resume(struct usb_interface *intf)
{
	struct usb_xpad *xpad = usb_get_intfdata(intf);
	struct input_dev *input = xpad->dev;
	int retval = 0;

	if (xpad->xtype == XTYPE_XBOX360W) {
		retval = xpad360w_start_input(xpad);
	} else {
		mutex_lock(&input->mutex);
		if (input->users) {
			retval = xpad_start_input(xpad);
		} else if (xpad->xtype == XTYPE_XBOXONE) {
			/*
			 * Even if there are no users, we'll send Xbox One pads
			 * the startup sequence so they don't sit there and
			 * blink until somebody opens the input device again.
			 */
			retval = xpad_start_xbox_one(xpad);
		}
		mutex_unlock(&input->mutex);
	}

	return retval;
}