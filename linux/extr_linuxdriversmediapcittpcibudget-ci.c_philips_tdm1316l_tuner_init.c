#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  td1316_init ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; } ;
struct TYPE_6__ {int /*<<< orphan*/  i2c_adap; } ;
struct budget_ci {int tuner_pll_address; TYPE_3__ budget; } ;
typedef  int /*<<< orphan*/  disable_mc44BC374c ;
struct TYPE_4__ {scalar_t__ priv; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int philips_tdm1316l_tuner_init(struct dvb_frontend *fe)
{
	struct budget_ci *budget_ci = (struct budget_ci *) fe->dvb->priv;
	static u8 td1316_init[] = { 0x0b, 0xf5, 0x85, 0xab };
	static u8 disable_mc44BC374c[] = { 0x1d, 0x74, 0xa0, 0x68 };
	struct i2c_msg tuner_msg = {.addr = budget_ci->tuner_pll_address,.flags = 0,.buf = td1316_init,.len =
			sizeof(td1316_init) };

	// setup PLL configuration
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1)
		return -EIO;
	msleep(1);

	// disable the mc44BC374c (do not check for errors)
	tuner_msg.addr = 0x65;
	tuner_msg.buf = disable_mc44BC374c;
	tuner_msg.len = sizeof(disable_mc44BC374c);
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1) {
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1);
	}

	return 0;
}