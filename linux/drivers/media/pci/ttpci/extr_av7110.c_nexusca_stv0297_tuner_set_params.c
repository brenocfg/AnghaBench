#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
struct av7110 {int /*<<< orphan*/  i2c_adap; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {struct av7110* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int nexusca_stv0297_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct av7110* av7110 = fe->dvb->priv;
	u32 div;
	u8 data[4];
	struct i2c_msg msg = { .addr = 0x63, .flags = 0, .buf = data, .len = sizeof(data) };
	struct i2c_msg readmsg = { .addr = 0x63, .flags = I2C_M_RD, .buf = data, .len = 1 };
	int i;

	div = (p->frequency + 36150000 + 31250) / 62500;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0xce;

	if (p->frequency < 45000000)
		return -EINVAL;
	else if (p->frequency < 137000000)
		data[3] = 0x01;
	else if (p->frequency < 403000000)
		data[3] = 0x02;
	else if (p->frequency < 860000000)
		data[3] = 0x04;
	else
		return -EINVAL;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&av7110->i2c_adap, &msg, 1) != 1) {
		printk("nexusca: pll transfer failed!\n");
		return -EIO;
	}

	// wait for PLL lock
	for(i = 0; i < 20; i++) {
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		if (i2c_transfer(&av7110->i2c_adap, &readmsg, 1) == 1)
			if (data[0] & 0x40) break;
		msleep(10);
	}

	return 0;
}