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
struct v4l2_frequency {int frequency; int /*<<< orphan*/  type; scalar_t__ tuner; } ;
struct saa7134_dev {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int /*<<< orphan*/  off ;
struct TYPE_3__ {struct saa7134_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_DIGITAL_TV ; 
 int /*<<< orphan*/  antenna_pwr ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int mt352_pinnacle_init (struct dvb_frontend*) ; 
 int /*<<< orphan*/  pinnacle_antenna_pwr (struct saa7134_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int mt352_pinnacle_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 off[] = { 0x00, 0xf1};
	u8 on[]  = { 0x00, 0x71};
	struct i2c_msg msg = {.addr=0x43, .flags=0, .buf=off, .len = sizeof(off)};

	struct saa7134_dev *dev = fe->dvb->priv;
	struct v4l2_frequency f;

	/* set frequency (mt2050) */
	f.tuner     = 0;
	f.type      = V4L2_TUNER_DIGITAL_TV;
	f.frequency = c->frequency / 1000 * 16 / 1000;
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(&dev->i2c_adap, &msg, 1);
	saa_call_all(dev, tuner, s_frequency, &f);
	msg.buf = on;
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(&dev->i2c_adap, &msg, 1);

	pinnacle_antenna_pwr(dev, antenna_pwr);

	/* mt352 setup */
	return mt352_pinnacle_init(fe);
}