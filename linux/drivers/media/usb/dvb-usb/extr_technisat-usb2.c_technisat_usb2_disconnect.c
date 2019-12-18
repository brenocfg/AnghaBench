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
struct usb_interface {int dummy; } ;
struct technisat_usb2_state {int /*<<< orphan*/  green_led_work; } ;
struct dvb_usb_device {struct technisat_usb2_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_usb_device_exit (struct usb_interface*) ; 
 struct dvb_usb_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void technisat_usb2_disconnect(struct usb_interface *intf)
{
	struct dvb_usb_device *dev = usb_get_intfdata(intf);

	/* work and stuff was only created when the device is is hot-state */
	if (dev != NULL) {
		struct technisat_usb2_state *state = dev->priv;
		if (state != NULL)
			cancel_delayed_work_sync(&state->green_led_work);
	}

	dvb_usb_device_exit(intf);
}