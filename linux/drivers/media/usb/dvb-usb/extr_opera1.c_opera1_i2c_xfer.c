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
struct i2c_msg {int addr; int flags; int len; int /*<<< orphan*/  buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int I2C_M_RD ; 
 int dvb_usb_opera1_debug ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  info (char*,int,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int opera1_usb_i2c_msgxfer (struct dvb_usb_device*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int opera1_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
			   int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i = 0, tmp = 0;

	if (!d)
		return -ENODEV;
	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		if ((tmp = opera1_usb_i2c_msgxfer(d,
					(msg[i].addr<<1)|(msg[i].flags&I2C_M_RD?0x01:0),
					msg[i].buf,
					msg[i].len
					)) != msg[i].len) {
			break;
		}
		if (dvb_usb_opera1_debug & 0x10)
			info("sending i2c message %d %d", tmp, msg[i].len);
	}
	mutex_unlock(&d->i2c_mutex);
	return num;
}