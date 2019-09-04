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
struct fc0013_priv {int xtal_freq; scalar_t__ dual_master; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct fc0013_priv* tuner_priv; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
#define  FC_XTAL_27_MHZ 130 
#define  FC_XTAL_28_8_MHZ 129 
#define  FC_XTAL_36_MHZ 128 
 int /*<<< orphan*/  err (char*,int) ; 
 int fc0013_writereg (struct fc0013_priv*,int,unsigned char) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int fc0013_init(struct dvb_frontend *fe)
{
	struct fc0013_priv *priv = fe->tuner_priv;
	int i, ret = 0;
	unsigned char reg[] = {
		0x00,	/* reg. 0x00: dummy */
		0x09,	/* reg. 0x01 */
		0x16,	/* reg. 0x02 */
		0x00,	/* reg. 0x03 */
		0x00,	/* reg. 0x04 */
		0x17,	/* reg. 0x05 */
		0x02,	/* reg. 0x06 */
		0x0a,	/* reg. 0x07: CHECK */
		0xff,	/* reg. 0x08: AGC Clock divide by 256, AGC gain 1/256,
			   Loop Bw 1/8 */
		0x6f,	/* reg. 0x09: enable LoopThrough */
		0xb8,	/* reg. 0x0a: Disable LO Test Buffer */
		0x82,	/* reg. 0x0b: CHECK */
		0xfc,	/* reg. 0x0c: depending on AGC Up-Down mode, may need 0xf8 */
		0x01,	/* reg. 0x0d: AGC Not Forcing & LNA Forcing, may need 0x02 */
		0x00,	/* reg. 0x0e */
		0x00,	/* reg. 0x0f */
		0x00,	/* reg. 0x10 */
		0x00,	/* reg. 0x11 */
		0x00,	/* reg. 0x12 */
		0x00,	/* reg. 0x13 */
		0x50,	/* reg. 0x14: DVB-t High Gain, UHF.
			   Middle Gain: 0x48, Low Gain: 0x40 */
		0x01,	/* reg. 0x15 */
	};

	switch (priv->xtal_freq) {
	case FC_XTAL_27_MHZ:
	case FC_XTAL_28_8_MHZ:
		reg[0x07] |= 0x20;
		break;
	case FC_XTAL_36_MHZ:
	default:
		break;
	}

	if (priv->dual_master)
		reg[0x0c] |= 0x02;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open I2C-gate */

	for (i = 1; i < sizeof(reg); i++) {
		ret = fc0013_writereg(priv, i, reg[i]);
		if (ret)
			break;
	}

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close I2C-gate */

	if (ret)
		err("fc0013_writereg failed: %d", ret);

	return ret;
}