#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct saa7134_dev {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_2__ {struct saa7134_dev* priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int SEC_VOLTAGE_18 ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static int md8800_set_voltage2(struct dvb_frontend *fe,
			       enum fe_sec_voltage voltage)
{
	struct saa7134_dev *dev = fe->dvb->priv;
	u8 wbuf[2] = { 0x1f, 00 };
	u8 rbuf;
	struct i2c_msg msg[] = { { .addr = 0x08, .flags = 0, .buf = wbuf, .len = 1 },
				 { .addr = 0x08, .flags = I2C_M_RD, .buf = &rbuf, .len = 1 } };

	if (i2c_transfer(&dev->i2c_adap, msg, 2) != 2)
		return -EIO;
	/* NOTE: this assumes that gpo1 is used, it might be bit 5 (gpo2) */
	if (voltage == SEC_VOLTAGE_18)
		wbuf[1] = rbuf | 0x10;
	else
		wbuf[1] = rbuf & 0xef;
	msg[0].len = 2;
	i2c_transfer(&dev->i2c_adap, msg, 1);
	return 0;
}