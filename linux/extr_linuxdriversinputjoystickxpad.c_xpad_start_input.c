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
struct usb_xpad {scalar_t__ xtype; int /*<<< orphan*/  irq_in; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ XTYPE_XBOXONE ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xpad_start_xbox_one (struct usb_xpad*) ; 

__attribute__((used)) static int xpad_start_input(struct usb_xpad *xpad)
{
	int error;

	if (usb_submit_urb(xpad->irq_in, GFP_KERNEL))
		return -EIO;

	if (xpad->xtype == XTYPE_XBOXONE) {
		error = xpad_start_xbox_one(xpad);
		if (error) {
			usb_kill_urb(xpad->irq_in);
			return error;
		}
	}

	return 0;
}