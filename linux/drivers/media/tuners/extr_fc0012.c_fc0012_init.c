#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fc0012_priv {TYPE_3__* i2c; TYPE_1__* cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_2__ ops; struct fc0012_priv* tuner_priv; } ;
typedef  int /*<<< orphan*/  reg ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int xtal_freq; scalar_t__ loop_through; scalar_t__ dual_master; } ;

/* Variables and functions */
#define  FC_XTAL_27_MHZ 130 
#define  FC_XTAL_28_8_MHZ 129 
#define  FC_XTAL_36_MHZ 128 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int fc0012_writereg (struct fc0012_priv*,int,unsigned char) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int fc0012_init(struct dvb_frontend *fe)
{
	struct fc0012_priv *priv = fe->tuner_priv;
	int i, ret = 0;
	unsigned char reg[] = {
		0x00,	/* dummy reg. 0 */
		0x05,	/* reg. 0x01 */
		0x10,	/* reg. 0x02 */
		0x00,	/* reg. 0x03 */
		0x00,	/* reg. 0x04 */
		0x0f,	/* reg. 0x05: may also be 0x0a */
		0x00,	/* reg. 0x06: divider 2, VCO slow */
		0x00,	/* reg. 0x07: may also be 0x0f */
		0xff,	/* reg. 0x08: AGC Clock divide by 256, AGC gain 1/256,
			   Loop Bw 1/8 */
		0x6e,	/* reg. 0x09: Disable LoopThrough, Enable LoopThrough: 0x6f */
		0xb8,	/* reg. 0x0a: Disable LO Test Buffer */
		0x82,	/* reg. 0x0b: Output Clock is same as clock frequency,
			   may also be 0x83 */
		0xfc,	/* reg. 0x0c: depending on AGC Up-Down mode, may need 0xf8 */
		0x02,	/* reg. 0x0d: AGC Not Forcing & LNA Forcing, 0x02 for DVB-T */
		0x00,	/* reg. 0x0e */
		0x00,	/* reg. 0x0f */
		0x00,	/* reg. 0x10: may also be 0x0d */
		0x00,	/* reg. 0x11 */
		0x1f,	/* reg. 0x12: Set to maximum gain */
		0x08,	/* reg. 0x13: Set to Middle Gain: 0x08,
			   Low Gain: 0x00, High Gain: 0x10, enable IX2: 0x80 */
		0x00,	/* reg. 0x14 */
		0x04,	/* reg. 0x15: Enable LNA COMPS */
	};

	switch (priv->cfg->xtal_freq) {
	case FC_XTAL_27_MHZ:
	case FC_XTAL_28_8_MHZ:
		reg[0x07] |= 0x20;
		break;
	case FC_XTAL_36_MHZ:
	default:
		break;
	}

	if (priv->cfg->dual_master)
		reg[0x0c] |= 0x02;

	if (priv->cfg->loop_through)
		reg[0x09] |= 0x01;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open I2C-gate */

	for (i = 1; i < sizeof(reg); i++) {
		ret = fc0012_writereg(priv, i, reg[i]);
		if (ret)
			break;
	}

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close I2C-gate */

	if (ret)
		dev_err(&priv->i2c->dev, "%s: fc0012_writereg failed: %d\n",
				KBUILD_MODNAME, ret);

	return ret;
}