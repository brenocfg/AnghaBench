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
struct i2c_msg {int flags; int len; int addr; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTSUPP ; 
 int I2C_M_IGNORE_NAK ; 
 int I2C_M_NOSTART ; 
 int I2C_M_NO_RD_ACK ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  M9206_I2C ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int m920x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int) ; 
 int m920x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m920x_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[], int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i, j;
	int ret = 0;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		if (msg[i].flags & (I2C_M_NO_RD_ACK | I2C_M_IGNORE_NAK | I2C_M_TEN) || msg[i].len == 0) {
			/* For a 0 byte message, I think sending the address
			 * to index 0x80|0x40 would be the correct thing to
			 * do.  However, zero byte messages are only used for
			 * probing, and since we don't know how to get the
			 * slave's ack, we can't probe. */
			ret = -ENOTSUPP;
			goto unlock;
		}
		/* Send START & address/RW bit */
		if (!(msg[i].flags & I2C_M_NOSTART)) {
			if ((ret = m920x_write(d->udev, M9206_I2C,
					(msg[i].addr << 1) |
					(msg[i].flags & I2C_M_RD ? 0x01 : 0), 0x80)) != 0)
				goto unlock;
			/* Should check for ack here, if we knew how. */
		}
		if (msg[i].flags & I2C_M_RD) {
			for (j = 0; j < msg[i].len; j++) {
				/* Last byte of transaction?
				 * Send STOP, otherwise send ACK. */
				int stop = (i+1 == num && j+1 == msg[i].len) ? 0x40 : 0x01;

				if ((ret = m920x_read(d->udev, M9206_I2C, 0x0,
						      0x20 | stop,
						      &msg[i].buf[j], 1)) != 0)
					goto unlock;
			}
		} else {
			for (j = 0; j < msg[i].len; j++) {
				/* Last byte of transaction? Then send STOP. */
				int stop = (i+1 == num && j+1 == msg[i].len) ? 0x40 : 0x00;

				if ((ret = m920x_write(d->udev, M9206_I2C, msg[i].buf[j], stop)) != 0)
					goto unlock;
				/* Should check for ack here too. */
			}
		}
	}
	ret = num;

 unlock:
	mutex_unlock(&d->i2c_mutex);

	return ret;
}