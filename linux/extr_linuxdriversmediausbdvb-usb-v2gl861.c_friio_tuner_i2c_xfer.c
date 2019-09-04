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
struct i2c_msg {int flags; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int I2C_M_RD ; 
 int friio_i2c_tuner_read (struct dvb_usb_device*,struct i2c_msg*) ; 
 int friio_i2c_tuner_write (struct dvb_usb_device*,struct i2c_msg*) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int friio_tuner_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
				int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i;

	if (num > 2)
		return -EINVAL;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		int ret;

		if (msg[i].flags & I2C_M_RD)
			ret = friio_i2c_tuner_read(d, &msg[i]);
		else
			ret = friio_i2c_tuner_write(d, &msg[i]);

		if (ret < 0)
			break;

		usleep_range(1000, 2000); /* avoid I2C errors */
	}

	mutex_unlock(&d->i2c_mutex);
	return i;
}