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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_pll_priv {int frequency; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/ * i2c; int /*<<< orphan*/  pll_i2c_address; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int /*<<< orphan*/  bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_1__ ops; struct dvb_pll_priv* tuner_priv; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int dvb_pll_configure (struct dvb_frontend*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int dvb_pll_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct dvb_pll_priv *priv = fe->tuner_priv;
	u8 buf[4];
	struct i2c_msg msg =
		{ .addr = priv->pll_i2c_address, .flags = 0,
		  .buf = buf, .len = sizeof(buf) };
	int result;
	u32 frequency = 0;

	if (priv->i2c == NULL)
		return -EINVAL;

	result = dvb_pll_configure(fe, buf, c->frequency);
	if (result < 0)
		return result;
	else
		frequency = result;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if ((result = i2c_transfer(priv->i2c, &msg, 1)) != 1) {
		return result;
	}

	priv->frequency = frequency;
	priv->bandwidth = c->bandwidth_hz;

	return 0;
}