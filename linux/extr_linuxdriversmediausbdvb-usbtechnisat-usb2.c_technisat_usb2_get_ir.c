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
struct ir_raw_event {int pulse; int duration; } ;
struct dvb_usb_device {int /*<<< orphan*/  rc_dev; int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  udev; struct technisat_usb2_state* priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FIRMWARE_CLOCK_DIVISOR ; 
 int FIRMWARE_CLOCK_TICK ; 
 int GET_IR_DATA_VENDOR_REQUEST ; 
 int MAXIMUM_IR_BIT_TIME_TICK_COUNT ; 
 int MINIMUM_IR_BIT_TRANSITION_TICK_COUNT ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int technisat_usb2_get_ir(struct dvb_usb_device *d)
{
	struct technisat_usb2_state *state = d->priv;
	u8 *buf = state->buf;
	u8 *b;
	int ret;
	struct ir_raw_event ev;

	buf[0] = GET_IR_DATA_VENDOR_REQUEST;
	buf[1] = 0x08;
	buf[2] = 0x8f;
	buf[3] = MINIMUM_IR_BIT_TRANSITION_TICK_COUNT;
	buf[4] = MAXIMUM_IR_BIT_TIME_TICK_COUNT;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;
	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
			GET_IR_DATA_VENDOR_REQUEST,
			USB_TYPE_VENDOR | USB_DIR_OUT,
			0, 0,
			buf, 5, 500);
	if (ret < 0)
		goto unlock;

	buf[1] = 0;
	buf[2] = 0;
	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0),
			GET_IR_DATA_VENDOR_REQUEST,
			USB_TYPE_VENDOR | USB_DIR_IN,
			0x8080, 0,
			buf, 62, 500);

unlock:
	mutex_unlock(&d->i2c_mutex);

	if (ret < 0)
		return ret;

	if (ret == 1)
		return 0; /* no key pressed */

	/* decoding */
	b = buf+1;

#if 0
	deb_rc("RC: %d ", ret);
	debug_dump(b, ret, deb_rc);
#endif

	ev.pulse = 0;
	while (1) {
		ev.pulse = !ev.pulse;
		ev.duration = (*b * FIRMWARE_CLOCK_DIVISOR * FIRMWARE_CLOCK_TICK) / 1000;
		ir_raw_event_store(d->rc_dev, &ev);

		b++;
		if (*b == 0xff) {
			ev.pulse = 0;
			ev.duration = 888888*2;
			ir_raw_event_store(d->rc_dev, &ev);
			break;
		}
	}

	ir_raw_event_handle(d->rc_dev);

	return 1;
}