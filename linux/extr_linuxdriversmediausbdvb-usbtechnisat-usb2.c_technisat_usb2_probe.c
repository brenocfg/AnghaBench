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
struct usb_device_id {int dummy; } ;
struct technisat_usb2_state {int /*<<< orphan*/  green_led_work; struct dvb_usb_device* dev; } ;
struct dvb_usb_device {struct technisat_usb2_state* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  disable_led_control ; 
 scalar_t__ dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dvb_usb_device**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  technisat_usb2_devices ; 
 int /*<<< orphan*/  technisat_usb2_green_led_control ; 

__attribute__((used)) static int technisat_usb2_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct dvb_usb_device *dev;

	if (dvb_usb_device_init(intf, &technisat_usb2_devices, THIS_MODULE,
				&dev, adapter_nr) != 0)
		return -ENODEV;

	if (dev) {
		struct technisat_usb2_state *state = dev->priv;
		state->dev = dev;

		if (!disable_led_control) {
			INIT_DELAYED_WORK(&state->green_led_work,
					technisat_usb2_green_led_control);
			schedule_delayed_work(&state->green_led_work,
					msecs_to_jiffies(500));
		}
	}

	return 0;
}