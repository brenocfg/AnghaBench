#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  int u64 ;
struct reg_val_mask {int member_0; int member_1; int member_2; scalar_t__ clock; int reg; int mask; int val; scalar_t__ adc; } ;
struct reg_val {int member_0; int member_1; int member_2; scalar_t__ clock; int reg; int mask; int val; scalar_t__ adc; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_16__ {int len; TYPE_11__* stat; } ;
struct TYPE_14__ {int len; TYPE_9__* stat; } ;
struct TYPE_25__ {int len; TYPE_7__* stat; } ;
struct TYPE_23__ {int len; TYPE_5__* stat; } ;
struct TYPE_21__ {int len; TYPE_3__* stat; } ;
struct TYPE_19__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_12__ post_bit_error; TYPE_10__ post_bit_count; TYPE_8__ block_error; TYPE_6__ block_count; TYPE_4__ cnr; TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct af9033_dev* demodulator_priv; } ;
struct TYPE_17__ {int tuner; int adc_multiplier; scalar_t__ clock; scalar_t__ ts_mode; scalar_t__ dyn0_clk; } ;
struct af9033_dev {int ts_mode_serial; int ts_mode_parallel; scalar_t__ bandwidth_hz; int /*<<< orphan*/  regmap; TYPE_13__ cfg; struct i2c_client* client; } ;
struct TYPE_26__ {void* scale; } ;
struct TYPE_24__ {void* scale; } ;
struct TYPE_22__ {void* scale; } ;
struct TYPE_20__ {void* scale; } ;
struct TYPE_18__ {void* scale; } ;
struct TYPE_15__ {void* scale; } ;

/* Variables and functions */
 scalar_t__ AF9033_TS_MODE_SERIAL ; 
 scalar_t__ AF9033_TS_MODE_USB ; 
#define  AF9033_TUNER_FC0011 139 
#define  AF9033_TUNER_FC0012 138 
#define  AF9033_TUNER_FC2580 137 
#define  AF9033_TUNER_IT9135_38 136 
#define  AF9033_TUNER_IT9135_51 135 
#define  AF9033_TUNER_IT9135_52 134 
#define  AF9033_TUNER_IT9135_60 133 
#define  AF9033_TUNER_IT9135_61 132 
#define  AF9033_TUNER_IT9135_62 131 
#define  AF9033_TUNER_MXL5007T 130 
#define  AF9033_TUNER_TDA18218 129 
#define  AF9033_TUNER_TUA9001 128 
 int ARRAY_SIZE (struct reg_val_mask*) ; 
 int ENODEV ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int af9033_wr_reg_val_tab (struct af9033_dev*,struct reg_val_mask const*,int) ; 
 struct reg_val_mask* clock_adc_lut ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 unsigned int div_u64 (int,int) ; 
 struct reg_val_mask* ofsm_init ; 
 struct reg_val_mask* ofsm_init_it9135_v1 ; 
 struct reg_val_mask* ofsm_init_it9135_v2 ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,unsigned int*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 struct reg_val_mask* tuner_init_fc0011 ; 
 struct reg_val_mask* tuner_init_fc0012 ; 
 struct reg_val_mask* tuner_init_fc2580 ; 
 struct reg_val_mask* tuner_init_it9135_38 ; 
 struct reg_val_mask* tuner_init_it9135_51 ; 
 struct reg_val_mask* tuner_init_it9135_52 ; 
 struct reg_val_mask* tuner_init_it9135_60 ; 
 struct reg_val_mask* tuner_init_it9135_61 ; 
 struct reg_val_mask* tuner_init_it9135_62 ; 
 struct reg_val_mask* tuner_init_mxl5007t ; 
 struct reg_val_mask* tuner_init_tda18218 ; 
 struct reg_val_mask* tuner_init_tua9001 ; 

__attribute__((used)) static int af9033_init(struct dvb_frontend *fe)
{
	struct af9033_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i, len;
	unsigned int utmp;
	const struct reg_val *init;
	u8 buf[4];
	struct reg_val_mask tab[] = {
		{ 0x80fb24, 0x00, 0x08 },
		{ 0x80004c, 0x00, 0xff },
		{ 0x00f641, dev->cfg.tuner, 0xff },
		{ 0x80f5ca, 0x01, 0x01 },
		{ 0x80f715, 0x01, 0x01 },
		{ 0x00f41f, 0x04, 0x04 },
		{ 0x00f41a, 0x01, 0x01 },
		{ 0x80f731, 0x00, 0x01 },
		{ 0x00d91e, 0x00, 0x01 },
		{ 0x00d919, 0x00, 0x01 },
		{ 0x80f732, 0x00, 0x01 },
		{ 0x00d91f, 0x00, 0x01 },
		{ 0x00d91a, 0x00, 0x01 },
		{ 0x80f730, 0x00, 0x01 },
		{ 0x80f778, 0x00, 0xff },
		{ 0x80f73c, 0x01, 0x01 },
		{ 0x80f776, 0x00, 0x01 },
		{ 0x00d8fd, 0x01, 0xff },
		{ 0x00d830, 0x01, 0xff },
		{ 0x00d831, 0x00, 0xff },
		{ 0x00d832, 0x00, 0xff },
		{ 0x80f985, dev->ts_mode_serial, 0x01 },
		{ 0x80f986, dev->ts_mode_parallel, 0x01 },
		{ 0x00d827, 0x00, 0xff },
		{ 0x00d829, 0x00, 0xff },
		{ 0x800045, dev->cfg.adc_multiplier, 0xff },
	};

	dev_dbg(&client->dev, "\n");

	/* Main clk control */
	utmp = div_u64((u64)dev->cfg.clock * 0x80000, 1000000);
	buf[0] = (utmp >>  0) & 0xff;
	buf[1] = (utmp >>  8) & 0xff;
	buf[2] = (utmp >> 16) & 0xff;
	buf[3] = (utmp >> 24) & 0xff;
	ret = regmap_bulk_write(dev->regmap, 0x800025, buf, 4);
	if (ret)
		goto err;

	dev_dbg(&client->dev, "clk=%u clk_cw=%08x\n", dev->cfg.clock, utmp);

	/* ADC clk control */
	for (i = 0; i < ARRAY_SIZE(clock_adc_lut); i++) {
		if (clock_adc_lut[i].clock == dev->cfg.clock)
			break;
	}
	if (i == ARRAY_SIZE(clock_adc_lut)) {
		dev_err(&client->dev, "Couldn't find ADC config for clock %d\n",
			dev->cfg.clock);
		goto err;
	}

	utmp = div_u64((u64)clock_adc_lut[i].adc * 0x80000, 1000000);
	buf[0] = (utmp >>  0) & 0xff;
	buf[1] = (utmp >>  8) & 0xff;
	buf[2] = (utmp >> 16) & 0xff;
	ret = regmap_bulk_write(dev->regmap, 0x80f1cd, buf, 3);
	if (ret)
		goto err;

	dev_dbg(&client->dev, "adc=%u adc_cw=%06x\n",
		clock_adc_lut[i].adc, utmp);

	/* Config register table */
	for (i = 0; i < ARRAY_SIZE(tab); i++) {
		ret = regmap_update_bits(dev->regmap, tab[i].reg, tab[i].mask,
					 tab[i].val);
		if (ret)
			goto err;
	}

	/* Demod clk output */
	if (dev->cfg.dyn0_clk) {
		ret = regmap_write(dev->regmap, 0x80fba8, 0x00);
		if (ret)
			goto err;
	}

	/* TS interface */
	if (dev->cfg.ts_mode == AF9033_TS_MODE_USB) {
		ret = regmap_update_bits(dev->regmap, 0x80f9a5, 0x01, 0x00);
		if (ret)
			goto err;
		ret = regmap_update_bits(dev->regmap, 0x80f9b5, 0x01, 0x01);
		if (ret)
			goto err;
	} else {
		ret = regmap_update_bits(dev->regmap, 0x80f990, 0x01, 0x00);
		if (ret)
			goto err;
		ret = regmap_update_bits(dev->regmap, 0x80f9b5, 0x01, 0x00);
		if (ret)
			goto err;
	}

	/* Demod core settings */
	dev_dbg(&client->dev, "load ofsm settings\n");
	switch (dev->cfg.tuner) {
	case AF9033_TUNER_IT9135_38:
	case AF9033_TUNER_IT9135_51:
	case AF9033_TUNER_IT9135_52:
		len = ARRAY_SIZE(ofsm_init_it9135_v1);
		init = ofsm_init_it9135_v1;
		break;
	case AF9033_TUNER_IT9135_60:
	case AF9033_TUNER_IT9135_61:
	case AF9033_TUNER_IT9135_62:
		len = ARRAY_SIZE(ofsm_init_it9135_v2);
		init = ofsm_init_it9135_v2;
		break;
	default:
		len = ARRAY_SIZE(ofsm_init);
		init = ofsm_init;
		break;
	}

	ret = af9033_wr_reg_val_tab(dev, init, len);
	if (ret)
		goto err;

	/* Demod tuner specific settings */
	dev_dbg(&client->dev, "load tuner specific settings\n");
	switch (dev->cfg.tuner) {
	case AF9033_TUNER_TUA9001:
		len = ARRAY_SIZE(tuner_init_tua9001);
		init = tuner_init_tua9001;
		break;
	case AF9033_TUNER_FC0011:
		len = ARRAY_SIZE(tuner_init_fc0011);
		init = tuner_init_fc0011;
		break;
	case AF9033_TUNER_MXL5007T:
		len = ARRAY_SIZE(tuner_init_mxl5007t);
		init = tuner_init_mxl5007t;
		break;
	case AF9033_TUNER_TDA18218:
		len = ARRAY_SIZE(tuner_init_tda18218);
		init = tuner_init_tda18218;
		break;
	case AF9033_TUNER_FC2580:
		len = ARRAY_SIZE(tuner_init_fc2580);
		init = tuner_init_fc2580;
		break;
	case AF9033_TUNER_FC0012:
		len = ARRAY_SIZE(tuner_init_fc0012);
		init = tuner_init_fc0012;
		break;
	case AF9033_TUNER_IT9135_38:
		len = ARRAY_SIZE(tuner_init_it9135_38);
		init = tuner_init_it9135_38;
		break;
	case AF9033_TUNER_IT9135_51:
		len = ARRAY_SIZE(tuner_init_it9135_51);
		init = tuner_init_it9135_51;
		break;
	case AF9033_TUNER_IT9135_52:
		len = ARRAY_SIZE(tuner_init_it9135_52);
		init = tuner_init_it9135_52;
		break;
	case AF9033_TUNER_IT9135_60:
		len = ARRAY_SIZE(tuner_init_it9135_60);
		init = tuner_init_it9135_60;
		break;
	case AF9033_TUNER_IT9135_61:
		len = ARRAY_SIZE(tuner_init_it9135_61);
		init = tuner_init_it9135_61;
		break;
	case AF9033_TUNER_IT9135_62:
		len = ARRAY_SIZE(tuner_init_it9135_62);
		init = tuner_init_it9135_62;
		break;
	default:
		dev_dbg(&client->dev, "unsupported tuner ID=%d\n",
			dev->cfg.tuner);
		ret = -ENODEV;
		goto err;
	}

	ret = af9033_wr_reg_val_tab(dev, init, len);
	if (ret)
		goto err;

	if (dev->cfg.ts_mode == AF9033_TS_MODE_SERIAL) {
		ret = regmap_update_bits(dev->regmap, 0x00d91c, 0x01, 0x01);
		if (ret)
			goto err;
		ret = regmap_update_bits(dev->regmap, 0x00d917, 0x01, 0x00);
		if (ret)
			goto err;
		ret = regmap_update_bits(dev->regmap, 0x00d916, 0x01, 0x00);
		if (ret)
			goto err;
	}

	switch (dev->cfg.tuner) {
	case AF9033_TUNER_IT9135_60:
	case AF9033_TUNER_IT9135_61:
	case AF9033_TUNER_IT9135_62:
		ret = regmap_write(dev->regmap, 0x800000, 0x01);
		if (ret)
			goto err;
	}

	dev->bandwidth_hz = 0; /* Force to program all parameters */
	/* Init stats here in order signal app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}