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
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_usb_device {int /*<<< orphan*/  rc_dev; int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  RC_PROTO_NEC ; 
 int /*<<< orphan*/  RC_SCANCODE_NEC (int,int) ; 
 int cxusb_i2c_xfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxusb_bluebird2_rc_query(struct dvb_usb_device *d)
{
	u8 ircode[4];
	struct i2c_msg msg = {
		.addr = 0x6b,
		.flags = I2C_M_RD,
		.buf = ircode,
		.len = 4
	};

	if (cxusb_i2c_xfer(&d->i2c_adap, &msg, 1) != 1)
		return 0;

	if (ircode[1] || ircode[2])
		rc_keydown(d->rc_dev, RC_PROTO_NEC,
			   RC_SCANCODE_NEC(~ircode[1] & 0xff, ircode[2]), 0);
	return 0;
}