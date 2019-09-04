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
typedef  int /*<<< orphan*/  tuner_buf ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; int bandwidth_hz; } ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_6__ {int /*<<< orphan*/  i2c_adap; } ;
struct budget_ci {TYPE_3__ budget; int /*<<< orphan*/  tuner_pll_address; } ;
struct TYPE_4__ {scalar_t__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tda1004x_writereg (struct dvb_frontend*,int,int) ; 

__attribute__((used)) static int philips_tdm1316l_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct budget_ci *budget_ci = (struct budget_ci *) fe->dvb->priv;
	u8 tuner_buf[4];
	struct i2c_msg tuner_msg = {.addr = budget_ci->tuner_pll_address,.flags = 0,.buf = tuner_buf,.len = sizeof(tuner_buf) };
	int tuner_frequency = 0;
	u8 band, cp, filter;

	// determine charge pump
	tuner_frequency = p->frequency + 36130000;
	if (tuner_frequency < 87000000)
		return -EINVAL;
	else if (tuner_frequency < 130000000)
		cp = 3;
	else if (tuner_frequency < 160000000)
		cp = 5;
	else if (tuner_frequency < 200000000)
		cp = 6;
	else if (tuner_frequency < 290000000)
		cp = 3;
	else if (tuner_frequency < 420000000)
		cp = 5;
	else if (tuner_frequency < 480000000)
		cp = 6;
	else if (tuner_frequency < 620000000)
		cp = 3;
	else if (tuner_frequency < 830000000)
		cp = 5;
	else if (tuner_frequency < 895000000)
		cp = 7;
	else
		return -EINVAL;

	// determine band
	if (p->frequency < 49000000)
		return -EINVAL;
	else if (p->frequency < 159000000)
		band = 1;
	else if (p->frequency < 444000000)
		band = 2;
	else if (p->frequency < 861000000)
		band = 4;
	else
		return -EINVAL;

	// setup PLL filter and TDA9889
	switch (p->bandwidth_hz) {
	case 6000000:
		tda1004x_writereg(fe, 0x0C, 0x14);
		filter = 0;
		break;

	case 7000000:
		tda1004x_writereg(fe, 0x0C, 0x80);
		filter = 0;
		break;

	case 8000000:
		tda1004x_writereg(fe, 0x0C, 0x14);
		filter = 1;
		break;

	default:
		return -EINVAL;
	}

	// calculate divisor
	// ((36130000+((1000000/6)/2)) + Finput)/(1000000/6)
	tuner_frequency = (((p->frequency / 1000) * 6) + 217280) / 1000;

	// setup tuner buffer
	tuner_buf[0] = tuner_frequency >> 8;
	tuner_buf[1] = tuner_frequency & 0xff;
	tuner_buf[2] = 0xca;
	tuner_buf[3] = (cp << 5) | (filter << 3) | band;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&budget_ci->budget.i2c_adap, &tuner_msg, 1) != 1)
		return -EIO;

	msleep(1);
	return 0;
}