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
typedef  void* u8 ;
typedef  int u16 ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; struct dib0700_state* priv; } ;
struct dib0700_state {int* buf; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int REQUEST_SET_I2C_PARAM ; 
 int /*<<< orphan*/  deb_info (char*,int,int,int,int) ; 
 int dib0700_ctrl_wr (struct dvb_usb_device*,int*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dib0700_set_i2c_speed(struct dvb_usb_device *d, u16 scl_kHz)
{
	struct dib0700_state *st = d->priv;
	u16 divider;
	int ret;

	if (scl_kHz == 0)
		return -EINVAL;

	if (mutex_lock_interruptible(&d->usb_mutex) < 0) {
		err("could not acquire lock");
		return -EINTR;
	}

	st->buf[0] = REQUEST_SET_I2C_PARAM;
	divider = (u16) (30000 / scl_kHz);
	st->buf[1] = 0;
	st->buf[2] = (u8) (divider >> 8);
	st->buf[3] = (u8) (divider & 0xff);
	divider = (u16) (72000 / scl_kHz);
	st->buf[4] = (u8) (divider >> 8);
	st->buf[5] = (u8) (divider & 0xff);
	divider = (u16) (72000 / scl_kHz); /* clock: 72MHz */
	st->buf[6] = (u8) (divider >> 8);
	st->buf[7] = (u8) (divider & 0xff);

	deb_info("setting I2C speed: %04x %04x %04x (%d kHz).",
		(st->buf[2] << 8) | (st->buf[3]), (st->buf[4] << 8) |
		st->buf[5], (st->buf[6] << 8) | st->buf[7], scl_kHz);

	ret = dib0700_ctrl_wr(d, st->buf, 8);
	mutex_unlock(&d->usb_mutex);

	return ret;
}