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
struct TYPE_2__ {int /*<<< orphan*/  adap; int /*<<< orphan*/  addr; } ;
struct tda18271_priv {unsigned char* tda18271_regs; TYPE_1__ i2c_props; } ;
struct i2c_msg {unsigned char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int DBG_REG ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int tda18271_debug ; 
 int /*<<< orphan*/  tda18271_dump_regs (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda18271_i2c_gate_ctrl (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tda_err (char*,int) ; 

int tda18271_read_regs(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	unsigned char buf = 0x00;
	int ret;
	struct i2c_msg msg[] = {
		{ .addr = priv->i2c_props.addr, .flags = 0,
		  .buf = &buf, .len = 1 },
		{ .addr = priv->i2c_props.addr, .flags = I2C_M_RD,
		  .buf = regs, .len = 16 }
	};

	tda18271_i2c_gate_ctrl(fe, 1);

	/* read all registers */
	ret = i2c_transfer(priv->i2c_props.adap, msg, 2);

	tda18271_i2c_gate_ctrl(fe, 0);

	if (ret != 2)
		tda_err("ERROR: i2c_transfer returned: %d\n", ret);

	if (tda18271_debug & DBG_REG)
		tda18271_dump_regs(fe, 0);

	return (ret == 2 ? 0 : ret);
}