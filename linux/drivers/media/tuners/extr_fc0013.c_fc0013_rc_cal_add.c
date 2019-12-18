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
struct fc0013_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct fc0013_priv* tuner_priv; } ;

/* Variables and functions */
 int fc0013_readreg (struct fc0013_priv*,int,int*) ; 
 int fc0013_writereg (struct fc0013_priv*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

int fc0013_rc_cal_add(struct dvb_frontend *fe, int rc_val)
{
	struct fc0013_priv *priv = fe->tuner_priv;
	int ret;
	u8 rc_cal;
	int val;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open I2C-gate */

	/* push rc_cal value, get rc_cal value */
	ret = fc0013_writereg(priv, 0x10, 0x00);
	if (ret)
		goto error_out;

	/* get rc_cal value */
	ret = fc0013_readreg(priv, 0x10, &rc_cal);
	if (ret)
		goto error_out;

	rc_cal &= 0x0f;

	val = (int)rc_cal + rc_val;

	/* forcing rc_cal */
	ret = fc0013_writereg(priv, 0x0d, 0x11);
	if (ret)
		goto error_out;

	/* modify rc_cal value */
	if (val > 15)
		ret = fc0013_writereg(priv, 0x10, 0x0f);
	else if (val < 0)
		ret = fc0013_writereg(priv, 0x10, 0x00);
	else
		ret = fc0013_writereg(priv, 0x10, (u8)val);

error_out:
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close I2C-gate */

	return ret;
}