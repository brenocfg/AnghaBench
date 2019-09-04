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
struct fc0011_priv {struct i2c_adapter* i2c; int /*<<< orphan*/  addr; } ;
struct fc0011_config {int /*<<< orphan*/  i2c_address; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct fc0011_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fc0011_tuner_ops ; 
 struct fc0011_priv* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dvb_frontend *fc0011_attach(struct dvb_frontend *fe,
				   struct i2c_adapter *i2c,
				   const struct fc0011_config *config)
{
	struct fc0011_priv *priv;

	priv = kzalloc(sizeof(struct fc0011_priv), GFP_KERNEL);
	if (!priv)
		return NULL;

	priv->i2c = i2c;
	priv->addr = config->i2c_address;

	fe->tuner_priv = priv;
	fe->ops.tuner_ops = fc0011_tuner_ops;

	dev_info(&priv->i2c->dev, "Fitipower FC0011 tuner attached\n");

	return fe;
}