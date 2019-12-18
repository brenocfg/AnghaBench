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
struct i2c_device_id {int dummy; } ;
struct device {struct helene_config* platform_data; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; struct device dev; } ;
struct helene_priv {int /*<<< orphan*/  i2c; int /*<<< orphan*/  i2c_address; int /*<<< orphan*/  xtal; int /*<<< orphan*/  set_tuner; int /*<<< orphan*/  set_tuner_data; } ;
struct helene_config {int /*<<< orphan*/  xtal; int /*<<< orphan*/  set_tuner_callback; int /*<<< orphan*/  set_tuner_priv; struct dvb_frontend* fe; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {struct helene_priv* tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct helene_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helene_tuner_ops ; 
 scalar_t__ helene_x_pon (struct helene_priv*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct helene_priv*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int helene_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct helene_config *config = client->dev.platform_data;
	struct dvb_frontend *fe = config->fe;
	struct device *dev = &client->dev;
	struct helene_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->i2c_address = client->addr;
	priv->i2c = client->adapter;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;
	priv->xtal = config->xtal;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	if (helene_x_pon(priv) != 0)
		return -EINVAL;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	memcpy(&fe->ops.tuner_ops, &helene_tuner_ops,
	       sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = priv;
	i2c_set_clientdata(client, priv);

	dev_info(dev, "Sony HELENE attached on addr=%x at I2C adapter %p\n",
		 priv->i2c_address, priv->i2c);

	return 0;
}