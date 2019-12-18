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
typedef  int u8 ;
struct technisat_usb2_state {int* buf; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  udev; struct technisat_usb2_state* priv; } ;
typedef  enum technisat_usb2_led_state { ____Placeholder_technisat_usb2_led_state } technisat_usb2_led_state ;

/* Variables and functions */
 int EAGAIN ; 
 int SET_GREEN_LED_VENDOR_REQUEST ; 
 int SET_RED_LED_VENDOR_REQUEST ; 
#define  TECH_LED_BLINK 130 
#define  TECH_LED_OFF 129 
#define  TECH_LED_ON 128 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 scalar_t__ disable_led_control ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int technisat_usb2_set_led(struct dvb_usb_device *d, int red,
				  enum technisat_usb2_led_state st)
{
	struct technisat_usb2_state *state = d->priv;
	u8 *led = state->buf;
	int ret;

	led[0] = red ? SET_RED_LED_VENDOR_REQUEST : SET_GREEN_LED_VENDOR_REQUEST;

	if (disable_led_control && st != TECH_LED_OFF)
		return 0;

	switch (st) {
	case TECH_LED_ON:
		led[1] = 0x82;
		break;
	case TECH_LED_BLINK:
		led[1] = 0x82;
		if (red) {
			led[2] = 0x02;
			led[3] = 10;
			led[4] = 10;
		} else {
			led[2] = 0xff;
			led[3] = 50;
			led[4] = 50;
		}
		led[5] = 1;
		break;

	default:
	case TECH_LED_OFF:
		led[1] = 0x80;
		break;
	}

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
		red ? SET_RED_LED_VENDOR_REQUEST : SET_GREEN_LED_VENDOR_REQUEST,
		USB_TYPE_VENDOR | USB_DIR_OUT,
		0, 0,
		led, 8, 500);

	mutex_unlock(&d->i2c_mutex);
	return ret;
}