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
struct qt1010_priv {struct i2c_adapter* i2c; struct qt1010_config* cfg; } ;
struct qt1010_config {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {struct qt1010_priv* tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qt1010_priv*) ; 
 struct qt1010_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ qt1010_readreg (struct qt1010_priv*,int,int*) ; 
 int /*<<< orphan*/  qt1010_tuner_ops ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

struct dvb_frontend * qt1010_attach(struct dvb_frontend *fe,
				    struct i2c_adapter *i2c,
				    struct qt1010_config *cfg)
{
	struct qt1010_priv *priv = NULL;
	u8 id;

	priv = kzalloc(sizeof(struct qt1010_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	priv->cfg = cfg;
	priv->i2c = i2c;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */


	/* Try to detect tuner chip. Probably this is not correct register. */
	if (qt1010_readreg(priv, 0x29, &id) != 0 || (id != 0x39)) {
		kfree(priv);
		return NULL;
	}

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	dev_info(&priv->i2c->dev,
			"%s: Quantek QT1010 successfully identified\n",
			KBUILD_MODNAME);

	memcpy(&fe->ops.tuner_ops, &qt1010_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	fe->tuner_priv = priv;
	return fe;
}