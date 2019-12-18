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
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int I2C_M_RD ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int technisat_usb2_i2c_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int technisat_usb2_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msg,
				int num)
{
	int ret = 0, i;
	struct dvb_usb_device *d = i2c_get_adapdata(adap);

	/* Ensure nobody else hits the i2c bus while we're sending our
	   sequence of messages, (such as the remote control thread) */
	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		if (i+1 < num && msg[i+1].flags & I2C_M_RD) {
			ret = technisat_usb2_i2c_access(d->udev, msg[i+1].addr,
						msg[i].buf, msg[i].len,
						msg[i+1].buf, msg[i+1].len);
			if (ret != 0)
				break;
			i++;
		} else {
			ret = technisat_usb2_i2c_access(d->udev, msg[i].addr,
						msg[i].buf, msg[i].len,
						NULL, 0);
			if (ret != 0)
				break;
		}
	}

	if (ret == 0)
		ret = i;

	mutex_unlock(&d->i2c_mutex);

	return ret;
}