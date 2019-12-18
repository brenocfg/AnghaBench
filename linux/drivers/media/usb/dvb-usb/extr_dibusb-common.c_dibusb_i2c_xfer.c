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
struct i2c_msg {int flags; int addr; int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int I2C_M_RD ; 
 scalar_t__ dibusb_i2c_msg (struct dvb_usb_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dibusb_i2c_xfer(struct i2c_adapter *adap,struct i2c_msg msg[],int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		/* write/read request */
		if (i+1 < num && (msg[i].flags & I2C_M_RD) == 0
					  && (msg[i+1].flags & I2C_M_RD)) {
			if (dibusb_i2c_msg(d, msg[i].addr, msg[i].buf,msg[i].len,
						msg[i+1].buf,msg[i+1].len) < 0)
				break;
			i++;
		} else if ((msg[i].flags & I2C_M_RD) == 0) {
			if (dibusb_i2c_msg(d, msg[i].addr, msg[i].buf,msg[i].len,NULL,0) < 0)
				break;
		} else if (msg[i].addr != 0x50) {
			/* 0x50 is the address of the eeprom - we need to protect it
			 * from dibusb's bad i2c implementation: reads without
			 * writing the offset before are forbidden */
			if (dibusb_i2c_msg(d, msg[i].addr, NULL, 0, msg[i].buf, msg[i].len) < 0)
				break;
		}
	}

	mutex_unlock(&d->i2c_mutex);
	return i;
}