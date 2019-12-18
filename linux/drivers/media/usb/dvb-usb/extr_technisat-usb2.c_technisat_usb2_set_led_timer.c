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

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  SET_LED_TIMER_DIVIDER_VENDOR_REQUEST ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int technisat_usb2_set_led_timer(struct dvb_usb_device *d, u8 red, u8 green)
{
	struct technisat_usb2_state *state = d->priv;
	u8 *b = state->buf;
	int ret;

	b[0] = 0;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
		SET_LED_TIMER_DIVIDER_VENDOR_REQUEST,
		USB_TYPE_VENDOR | USB_DIR_OUT,
		(red << 8) | green, 0,
		b, 1, 500);

	mutex_unlock(&d->i2c_mutex);

	return ret;
}