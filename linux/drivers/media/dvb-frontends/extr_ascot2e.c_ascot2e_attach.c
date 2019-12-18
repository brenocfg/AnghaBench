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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {struct ascot2e_priv* tuner_priv; TYPE_1__ ops; } ;
struct ascot2e_priv {int i2c_address; struct i2c_adapter* i2c; int /*<<< orphan*/  state; int /*<<< orphan*/  set_tuner; int /*<<< orphan*/  set_tuner_data; } ;
struct ascot2e_config {int i2c_address; int /*<<< orphan*/  set_tuner_callback; int /*<<< orphan*/  set_tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STATE_SLEEP ; 
 int /*<<< orphan*/  ascot2e_tuner_ops ; 
 int /*<<< orphan*/  ascot2e_write_reg (struct ascot2e_priv*,int,int) ; 
 int /*<<< orphan*/  ascot2e_write_regs (struct ascot2e_priv*,int,int*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,struct i2c_adapter*) ; 
 struct ascot2e_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

struct dvb_frontend *ascot2e_attach(struct dvb_frontend *fe,
				    const struct ascot2e_config *config,
				    struct i2c_adapter *i2c)
{
	u8 data[4];
	struct ascot2e_priv *priv = NULL;

	priv = kzalloc(sizeof(struct ascot2e_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;
	priv->i2c_address = (config->i2c_address >> 1);
	priv->i2c = i2c;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* 16 MHz xTal frequency */
	data[0] = 16;
	/* VCO current setting */
	data[1] = 0x06;
	/* Logic wake up, CPU boot */
	data[2] = 0xC4;
	data[3] = 0x40;
	ascot2e_write_regs(priv, 0x01, data, 4);
	/* RFVGA optimization setting (RF_DIST0 - RF_DIST2) */
	data[0] = 0x10;
	data[1] = 0x3F;
	data[2] = 0x25;
	ascot2e_write_regs(priv, 0x22, data, 3);
	/* PLL mode setting */
	ascot2e_write_reg(priv, 0x28, 0x1e);
	/* RSSI setting */
	ascot2e_write_reg(priv, 0x59, 0x04);
	/* TODO check CPU HW error state here */
	msleep(80);
	/* Xtal oscillator current control setting */
	ascot2e_write_reg(priv, 0x4c, 0x01);
	/* XOSC_SEL=100uA */
	ascot2e_write_reg(priv, 0x07, 0x04);
	/* CPU deep sleep */
	ascot2e_write_reg(priv, 0x04, 0x00);
	/* Logic sleep */
	ascot2e_write_reg(priv, 0x03, 0xc0);
	/* Power save setting */
	data[0] = 0x00;
	data[1] = 0x04;
	ascot2e_write_regs(priv, 0x14, data, 2);
	ascot2e_write_reg(priv, 0x50, 0x01);
	priv->state = STATE_SLEEP;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	memcpy(&fe->ops.tuner_ops, &ascot2e_tuner_ops,
				sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = priv;
	dev_info(&priv->i2c->dev,
		"Sony ASCOT2E attached on addr=%x at I2C adapter %p\n",
		priv->i2c_address, priv->i2c);
	return fe;
}