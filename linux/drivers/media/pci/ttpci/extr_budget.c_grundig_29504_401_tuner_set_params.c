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
struct i2c_msg {int* buf; int len; int addr; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {int* tuner_priv; TYPE_2__ ops; TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
struct budget {int /*<<< orphan*/  i2c_adap; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {struct budget* priv; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int grundig_29504_401_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct budget *budget = fe->dvb->priv;
	u8 *tuner_addr = fe->tuner_priv;
	u32 div;
	u8 cfg, cpump, band_select;
	u8 data[4];
	struct i2c_msg msg = { .flags = 0, .buf = data, .len = sizeof(data) };

	if (tuner_addr)
		msg.addr = *tuner_addr;
	else
		msg.addr = 0x61;

	div = (36125000 + c->frequency) / 166666;

	cfg = 0x88;

	if (c->frequency < 175000000)
		cpump = 2;
	else if (c->frequency < 390000000)
		cpump = 1;
	else if (c->frequency < 470000000)
		cpump = 2;
	else if (c->frequency < 750000000)
		cpump = 1;
	else
		cpump = 3;

	if (c->frequency < 175000000)
		band_select = 0x0e;
	else if (c->frequency < 470000000)
		band_select = 0x05;
	else
		band_select = 0x03;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = ((div >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_select;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer (&budget->i2c_adap, &msg, 1) != 1) return -EIO;
	return 0;
}