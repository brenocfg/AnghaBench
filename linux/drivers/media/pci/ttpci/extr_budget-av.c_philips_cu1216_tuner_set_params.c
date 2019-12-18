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
struct i2c_msg {int addr; int* buf; int len; scalar_t__ flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
struct budget {int /*<<< orphan*/  i2c_adap; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int CU1216_IF ; 
 int EIO ; 
 scalar_t__ I2C_M_RD ; 
 int TUNER_MUL ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int philips_cu1216_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct budget *budget = (struct budget *) fe->dvb->priv;
	u8 buf[6];
	struct i2c_msg msg = {.addr = 0x60,.flags = 0,.buf = buf,.len = sizeof(buf) };
	int i;

#define CU1216_IF 36125000
#define TUNER_MUL 62500

	u32 div = (c->frequency + CU1216_IF + TUNER_MUL / 2) / TUNER_MUL;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = 0xce;
	buf[3] = (c->frequency < 150000000 ? 0x01 :
		  c->frequency < 445000000 ? 0x02 : 0x04);
	buf[4] = 0xde;
	buf[5] = 0x20;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&budget->i2c_adap, &msg, 1) != 1)
		return -EIO;

	/* wait for the pll lock */
	msg.flags = I2C_M_RD;
	msg.len = 1;
	for (i = 0; i < 20; i++) {
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		if (i2c_transfer(&budget->i2c_adap, &msg, 1) == 1 && (buf[0] & 0x40))
			break;
		msleep(10);
	}

	/* switch the charge pump to the lower current */
	msg.flags = 0;
	msg.len = 2;
	msg.buf = &buf[2];
	buf[2] &= ~0x40;
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&budget->i2c_adap, &msg, 1) != 1)
		return -EIO;

	return 0;
}