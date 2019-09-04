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
struct usb_xpad {int input_created; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpad_led_disconnect (struct usb_xpad*) ; 

__attribute__((used)) static void xpad_deinit_input(struct usb_xpad *xpad)
{
	if (xpad->input_created) {
		xpad->input_created = false;
		xpad_led_disconnect(xpad);
		input_unregister_device(xpad->dev);
	}
}