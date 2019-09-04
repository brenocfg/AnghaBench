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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct helene_priv {int i2c_address; struct i2c_adapter* i2c; int /*<<< orphan*/  xtal; int /*<<< orphan*/  set_tuner; int /*<<< orphan*/  set_tuner_data; } ;
struct helene_config {int i2c_address; int /*<<< orphan*/  xtal; int /*<<< orphan*/  set_tuner_callback; int /*<<< orphan*/  set_tuner_priv; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {struct helene_priv* tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,struct i2c_adapter*) ; 
 int /*<<< orphan*/  helene_tuner_ops_s ; 
 scalar_t__ helene_x_pon (struct helene_priv*) ; 
 int /*<<< orphan*/  kfree (struct helene_priv*) ; 
 struct helene_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

struct dvb_frontend *helene_attach_s(struct dvb_frontend *fe,
		const struct helene_config *config,
		struct i2c_adapter *i2c)
{
	struct helene_priv *priv = NULL;

	priv = kzalloc(sizeof(struct helene_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;
	priv->i2c_address = (config->i2c_address >> 1);
	priv->i2c = i2c;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;
	priv->xtal = config->xtal;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	if (helene_x_pon(priv) != 0) {
		kfree(priv);
		return NULL;
	}

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	memcpy(&fe->ops.tuner_ops, &helene_tuner_ops_s,
			sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = priv;
	dev_info(&priv->i2c->dev,
			"Sony HELENE Sat attached on addr=%x at I2C adapter %p\n",
			priv->i2c_address, priv->i2c);
	return fe;
}