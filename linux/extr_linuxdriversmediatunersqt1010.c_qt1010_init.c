#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct qt1010_priv {size_t reg20_init_val; size_t reg25_init_val; size_t reg1f_init_val; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {TYPE_1__ ops; struct dtv_frontend_properties dtv_property_cache; struct qt1010_priv* tuner_priv; } ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int oper; int val; int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ qt1010_i2c_oper_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  QT1010_M1 130 
#define  QT1010_RD 129 
#define  QT1010_WR 128 
 int qt1010_init_meas1 (struct qt1010_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*) ; 
 int qt1010_init_meas2 (struct qt1010_priv*,size_t,size_t*) ; 
 int qt1010_readreg (struct qt1010_priv*,int /*<<< orphan*/ ,size_t*) ; 
 int qt1010_set_params (struct dvb_frontend*) ; 
 int qt1010_writereg (struct qt1010_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int qt1010_init(struct dvb_frontend *fe)
{
	struct qt1010_priv *priv = fe->tuner_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int err = 0;
	u8 i, tmpval, *valptr = NULL;

	static const qt1010_i2c_oper_t i2c_data[] = {
		{ QT1010_WR, 0x01, 0x80 },
		{ QT1010_WR, 0x0d, 0x84 },
		{ QT1010_WR, 0x0e, 0xb7 },
		{ QT1010_WR, 0x2a, 0x23 },
		{ QT1010_WR, 0x2c, 0xdc },
		{ QT1010_M1, 0x25, 0x40 }, /* get reg 25 init value */
		{ QT1010_M1, 0x81, 0xff }, /* get reg 25 init value */
		{ QT1010_WR, 0x2b, 0x70 },
		{ QT1010_WR, 0x2a, 0x23 },
		{ QT1010_M1, 0x26, 0x08 },
		{ QT1010_M1, 0x82, 0xff },
		{ QT1010_WR, 0x05, 0x14 },
		{ QT1010_WR, 0x06, 0x44 },
		{ QT1010_WR, 0x07, 0x28 },
		{ QT1010_WR, 0x08, 0x0b },
		{ QT1010_WR, 0x11, 0xfd },
		{ QT1010_M1, 0x22, 0x0d },
		{ QT1010_M1, 0xd0, 0xff },
		{ QT1010_WR, 0x06, 0x40 },
		{ QT1010_WR, 0x16, 0xf0 },
		{ QT1010_WR, 0x02, 0x38 },
		{ QT1010_WR, 0x03, 0x18 },
		{ QT1010_WR, 0x20, 0xe0 },
		{ QT1010_M1, 0x1f, 0x20 }, /* get reg 1f init value */
		{ QT1010_M1, 0x84, 0xff }, /* get reg 1f init value */
		{ QT1010_RD, 0x20, 0x20 }, /* get reg 20 init value */
		{ QT1010_WR, 0x03, 0x19 },
		{ QT1010_WR, 0x02, 0x3f },
		{ QT1010_WR, 0x21, 0x53 },
		{ QT1010_RD, 0x21, 0xff },
		{ QT1010_WR, 0x11, 0xfd },
		{ QT1010_WR, 0x05, 0x34 },
		{ QT1010_WR, 0x06, 0x44 },
		{ QT1010_WR, 0x08, 0x08 }
	};

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */

	for (i = 0; i < ARRAY_SIZE(i2c_data); i++) {
		switch (i2c_data[i].oper) {
		case QT1010_WR:
			err = qt1010_writereg(priv, i2c_data[i].reg,
					      i2c_data[i].val);
			break;
		case QT1010_RD:
			if (i2c_data[i].val == 0x20)
				valptr = &priv->reg20_init_val;
			else
				valptr = &tmpval;
			err = qt1010_readreg(priv, i2c_data[i].reg, valptr);
			break;
		case QT1010_M1:
			if (i2c_data[i].val == 0x25)
				valptr = &priv->reg25_init_val;
			else if (i2c_data[i].val == 0x1f)
				valptr = &priv->reg1f_init_val;
			else
				valptr = &tmpval;

			BUG_ON(i >= ARRAY_SIZE(i2c_data) - 1);

			err = qt1010_init_meas1(priv, i2c_data[i+1].reg,
						i2c_data[i].reg,
						i2c_data[i].val, valptr);
			i++;
			break;
		}
		if (err)
			return err;
	}

	for (i = 0x31; i < 0x3a; i++) /* 0x31 - 0x39 */
		if ((err = qt1010_init_meas2(priv, i, &tmpval)))
			return err;

	if (!c->frequency)
		c->frequency = 545000000; /* Sigmatek DVB-110 545000000 */
				      /* MSI Megasky 580 GL861 533000000 */
	return qt1010_set_params(fe);
}