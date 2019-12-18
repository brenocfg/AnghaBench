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
struct i2c_msg {int addr; int* buf; int len; } ;
struct i2c_adapter {int dummy; } ;
struct dw2102_state {int* data; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  data_mutex; struct dw2102_state* priv; } ;

/* Variables and functions */
#define  DW2102_RC_QUERY 129 
 int EAGAIN ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
#define  SU3000_STREAM_CTRL 128 
 int /*<<< orphan*/  dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int su3000_i2c_transfer(struct i2c_adapter *adap, struct i2c_msg msg[],
								int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct dw2102_state *state;

	if (!d)
		return -ENODEV;

	state = d->priv;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;
	if (mutex_lock_interruptible(&d->data_mutex) < 0) {
		mutex_unlock(&d->i2c_mutex);
		return -EAGAIN;
	}

	switch (num) {
	case 1:
		switch (msg[0].addr) {
		case SU3000_STREAM_CTRL:
			state->data[0] = msg[0].buf[0] + 0x36;
			state->data[1] = 3;
			state->data[2] = 0;
			if (dvb_usb_generic_rw(d, state->data, 3,
					state->data, 0, 0) < 0)
				err("i2c transfer failed.");
			break;
		case DW2102_RC_QUERY:
			state->data[0] = 0x10;
			if (dvb_usb_generic_rw(d, state->data, 1,
					state->data, 2, 0) < 0)
				err("i2c transfer failed.");
			msg[0].buf[1] = state->data[0];
			msg[0].buf[0] = state->data[1];
			break;
		default:
			if (3 + msg[0].len > sizeof(state->data)) {
				warn("i2c wr: len=%d is too big!\n",
				     msg[0].len);
				num = -EOPNOTSUPP;
				break;
			}

			/* always i2c write*/
			state->data[0] = 0x08;
			state->data[1] = msg[0].addr;
			state->data[2] = msg[0].len;

			memcpy(&state->data[3], msg[0].buf, msg[0].len);

			if (dvb_usb_generic_rw(d, state->data, msg[0].len + 3,
						state->data, 1, 0) < 0)
				err("i2c transfer failed.");

		}
		break;
	case 2:
		/* always i2c read */
		if (4 + msg[0].len > sizeof(state->data)) {
			warn("i2c rd: len=%d is too big!\n",
			     msg[0].len);
			num = -EOPNOTSUPP;
			break;
		}
		if (1 + msg[1].len > sizeof(state->data)) {
			warn("i2c rd: len=%d is too big!\n",
			     msg[1].len);
			num = -EOPNOTSUPP;
			break;
		}

		state->data[0] = 0x09;
		state->data[1] = msg[0].len;
		state->data[2] = msg[1].len;
		state->data[3] = msg[0].addr;
		memcpy(&state->data[4], msg[0].buf, msg[0].len);

		if (dvb_usb_generic_rw(d, state->data, msg[0].len + 4,
					state->data, msg[1].len + 1, 0) < 0)
			err("i2c transfer failed.");

		memcpy(msg[1].buf, &state->data[1], msg[1].len);
		break;
	default:
		warn("more than 2 i2c messages at a time is not handled yet.");
		break;
	}
	mutex_unlock(&d->data_mutex);
	mutex_unlock(&d->i2c_mutex);
	return num;
}