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
typedef  int u8 ;
struct ts2020_reg_val {int member_0; int member_1; int reg; int val; } ;
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct ts2020_priv {scalar_t__ tuner; int clk_out_div; int clk_out; TYPE_3__ stat_work; int /*<<< orphan*/  regmap; scalar_t__ loop_through; } ;
struct TYPE_5__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ strength; } ;
struct dvb_frontend {struct ts2020_priv* tuner_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_4__ {scalar_t__ uvalue; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ts2020_reg_val const*) ; 
 int /*<<< orphan*/  FE_SCALE_DECIBEL ; 
#define  TS2020_CLK_OUT_DISABLED 130 
#define  TS2020_CLK_OUT_ENABLED 129 
#define  TS2020_CLK_OUT_ENABLED_XTALOUT 128 
 scalar_t__ TS2020_M88TS2020 ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ts2020_stat_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ts2020_init(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct ts2020_priv *priv = fe->tuner_priv;
	int i;
	u8 u8tmp;

	if (priv->tuner == TS2020_M88TS2020) {
		regmap_write(priv->regmap, 0x42, 0x73);
		regmap_write(priv->regmap, 0x05, priv->clk_out_div);
		regmap_write(priv->regmap, 0x20, 0x27);
		regmap_write(priv->regmap, 0x07, 0x02);
		regmap_write(priv->regmap, 0x11, 0xff);
		regmap_write(priv->regmap, 0x60, 0xf9);
		regmap_write(priv->regmap, 0x08, 0x01);
		regmap_write(priv->regmap, 0x00, 0x41);
	} else {
		static const struct ts2020_reg_val reg_vals[] = {
			{0x7d, 0x9d},
			{0x7c, 0x9a},
			{0x7a, 0x76},
			{0x3b, 0x01},
			{0x63, 0x88},
			{0x61, 0x85},
			{0x22, 0x30},
			{0x30, 0x40},
			{0x20, 0x23},
			{0x24, 0x02},
			{0x12, 0xa0},
		};

		regmap_write(priv->regmap, 0x00, 0x01);
		regmap_write(priv->regmap, 0x00, 0x03);

		switch (priv->clk_out) {
		case TS2020_CLK_OUT_DISABLED:
			u8tmp = 0x60;
			break;
		case TS2020_CLK_OUT_ENABLED:
			u8tmp = 0x70;
			regmap_write(priv->regmap, 0x05, priv->clk_out_div);
			break;
		case TS2020_CLK_OUT_ENABLED_XTALOUT:
			u8tmp = 0x6c;
			break;
		default:
			u8tmp = 0x60;
			break;
		}

		regmap_write(priv->regmap, 0x42, u8tmp);

		if (priv->loop_through)
			u8tmp = 0xec;
		else
			u8tmp = 0x6c;

		regmap_write(priv->regmap, 0x62, u8tmp);

		for (i = 0; i < ARRAY_SIZE(reg_vals); i++)
			regmap_write(priv->regmap, reg_vals[i].reg,
				     reg_vals[i].val);
	}

	/* Initialise v5 stats here */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].uvalue = 0;

	/* Start statistics polling by invoking the work function */
	ts2020_stat_work(&priv->stat_work.work);
	return 0;
}