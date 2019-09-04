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
struct mt2060_priv {TYPE_1__* cfg; scalar_t__ sleep; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_2__ ops; struct mt2060_priv* tuner_priv; } ;
struct TYPE_3__ {int clock_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MISC_CTRL ; 
 int /*<<< orphan*/  REG_VGAG ; 
 int mt2060_writereg (struct mt2060_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mt2060_init(struct dvb_frontend *fe)
{
	struct mt2060_priv *priv = fe->tuner_priv;
	int ret;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */

	if (priv->sleep) {
		ret = mt2060_writereg(priv, REG_MISC_CTRL, 0x20);
		if (ret)
			goto err_i2c_gate_ctrl;
	}

	ret = mt2060_writereg(priv, REG_VGAG,
			      (priv->cfg->clock_out << 6) | 0x33);

err_i2c_gate_ctrl:
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	return ret;
}