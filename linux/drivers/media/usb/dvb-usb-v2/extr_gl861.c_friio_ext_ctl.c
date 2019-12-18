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
typedef  int u32 ;
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EREMOTEIO ; 
 int FRIIO_CTL_CLK ; 
 int FRIIO_CTL_LED ; 
 int FRIIO_CTL_LNB ; 
 int FRIIO_CTL_STROBE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int friio_ext_ctl(struct dvb_usb_device *d,
			    u32 sat_color, int power_on)
{
	int i, ret;
	struct i2c_msg msg;
	u8 *buf;
	u32 mask;
	u8 power = (power_on) ? FRIIO_CTL_LNB : 0;

	buf = kmalloc(2, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	msg.addr = 0x00;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = buf;
	buf[0] = 0x00;

	/* send 2bit header (&B10) */
	buf[1] = power | FRIIO_CTL_LED | FRIIO_CTL_STROBE;
	ret = i2c_transfer(&d->i2c_adap, &msg, 1);
	buf[1] |= FRIIO_CTL_CLK;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);

	buf[1] = power | FRIIO_CTL_STROBE;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);
	buf[1] |= FRIIO_CTL_CLK;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);

	/* send 32bit(satur, R, G, B) data in serial */
	mask = 1UL << 31;
	for (i = 0; i < 32; i++) {
		buf[1] = power | FRIIO_CTL_STROBE;
		if (sat_color & mask)
			buf[1] |= FRIIO_CTL_LED;
		ret += i2c_transfer(&d->i2c_adap, &msg, 1);
		buf[1] |= FRIIO_CTL_CLK;
		ret += i2c_transfer(&d->i2c_adap, &msg, 1);
		mask >>= 1;
	}

	/* set the strobe off */
	buf[1] = power;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);
	buf[1] |= FRIIO_CTL_CLK;
	ret += i2c_transfer(&d->i2c_adap, &msg, 1);

	kfree(buf);
	return (ret == 70) ? 0 : -EREMOTEIO;
}