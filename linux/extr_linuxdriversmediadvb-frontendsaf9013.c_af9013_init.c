#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int u8 ;
typedef  int u64 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct af9013_state* demodulator_priv; } ;
struct af9013_state {unsigned int* api_version; int clk; int tuner; int ts_output_pin; int ts_mode; int first_tune; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct af9013_reg_mask_val {int reg; int mask; int val; } ;

/* Variables and functions */
#define  AF9013_TUNER_ENV77H11D5 140 
#define  AF9013_TUNER_MC44S803 139 
#define  AF9013_TUNER_MT2060 138 
#define  AF9013_TUNER_MT2060_2 137 
#define  AF9013_TUNER_MXL5003D 136 
#define  AF9013_TUNER_MXL5005D 135 
#define  AF9013_TUNER_MXL5005R 134 
#define  AF9013_TUNER_MXL5007T 133 
#define  AF9013_TUNER_QT1010 132 
#define  AF9013_TUNER_QT1010A 131 
#define  AF9013_TUNER_TDA18218 130 
#define  AF9013_TUNER_TDA18271 129 
#define  AF9013_TUNER_UNKNOWN 128 
 int ARRAY_SIZE (struct af9013_reg_mask_val*) ; 
 int EINVAL ; 
 struct af9013_reg_mask_val* demod_init_tab ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int div_u64 (int,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,unsigned int*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 struct af9013_reg_mask_val* tuner_init_tab_env77h11d5 ; 
 struct af9013_reg_mask_val* tuner_init_tab_mc44s803 ; 
 struct af9013_reg_mask_val* tuner_init_tab_mt2060 ; 
 struct af9013_reg_mask_val* tuner_init_tab_mt2060_2 ; 
 struct af9013_reg_mask_val* tuner_init_tab_mxl5003d ; 
 struct af9013_reg_mask_val* tuner_init_tab_mxl5005 ; 
 struct af9013_reg_mask_val* tuner_init_tab_qt1010 ; 
 struct af9013_reg_mask_val* tuner_init_tab_tda18271 ; 
 struct af9013_reg_mask_val* tuner_init_tab_unknown ; 

__attribute__((used)) static int af9013_init(struct dvb_frontend *fe)
{
	struct af9013_state *state = fe->demodulator_priv;
	struct i2c_client *client = state->client;
	int ret, i, len;
	unsigned int utmp;
	u8 buf[3];
	const struct af9013_reg_mask_val *tab;

	dev_dbg(&client->dev, "\n");

	/* ADC on */
	ret = regmap_update_bits(state->regmap, 0xd73a, 0x08, 0x00);
	if (ret)
		goto err;

	/* Clear reset */
	ret = regmap_update_bits(state->regmap, 0xd417, 0x02, 0x00);
	if (ret)
		goto err;

	/* Disable reset */
	ret = regmap_update_bits(state->regmap, 0xd417, 0x10, 0x00);
	if (ret)
		goto err;

	/* write API version to firmware */
	ret = regmap_bulk_write(state->regmap, 0x9bf2, state->api_version, 4);
	if (ret)
		goto err;

	/* program ADC control */
	switch (state->clk) {
	case 28800000: /* 28.800 MHz */
		utmp = 0;
		break;
	case 20480000: /* 20.480 MHz */
		utmp = 1;
		break;
	case 28000000: /* 28.000 MHz */
		utmp = 2;
		break;
	case 25000000: /* 25.000 MHz */
		utmp = 3;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	ret = regmap_update_bits(state->regmap, 0x9bd2, 0x0f, utmp);
	if (ret)
		goto err;

	utmp = div_u64((u64)state->clk * 0x80000, 1000000);
	buf[0] = (utmp >>  0) & 0xff;
	buf[1] = (utmp >>  8) & 0xff;
	buf[2] = (utmp >> 16) & 0xff;
	ret = regmap_bulk_write(state->regmap, 0xd180, buf, 3);
	if (ret)
		goto err;

	/* Demod core settings */
	dev_dbg(&client->dev, "load demod core settings\n");
	len = ARRAY_SIZE(demod_init_tab);
	tab = demod_init_tab;
	for (i = 0; i < len; i++) {
		ret = regmap_update_bits(state->regmap, tab[i].reg, tab[i].mask,
					 tab[i].val);
		if (ret)
			goto err;
	}

	/* Demod tuner specific settings */
	dev_dbg(&client->dev, "load tuner specific settings\n");
	switch (state->tuner) {
	case AF9013_TUNER_MXL5003D:
		len = ARRAY_SIZE(tuner_init_tab_mxl5003d);
		tab = tuner_init_tab_mxl5003d;
		break;
	case AF9013_TUNER_MXL5005D:
	case AF9013_TUNER_MXL5005R:
	case AF9013_TUNER_MXL5007T:
		len = ARRAY_SIZE(tuner_init_tab_mxl5005);
		tab = tuner_init_tab_mxl5005;
		break;
	case AF9013_TUNER_ENV77H11D5:
		len = ARRAY_SIZE(tuner_init_tab_env77h11d5);
		tab = tuner_init_tab_env77h11d5;
		break;
	case AF9013_TUNER_MT2060:
		len = ARRAY_SIZE(tuner_init_tab_mt2060);
		tab = tuner_init_tab_mt2060;
		break;
	case AF9013_TUNER_MC44S803:
		len = ARRAY_SIZE(tuner_init_tab_mc44s803);
		tab = tuner_init_tab_mc44s803;
		break;
	case AF9013_TUNER_QT1010:
	case AF9013_TUNER_QT1010A:
		len = ARRAY_SIZE(tuner_init_tab_qt1010);
		tab = tuner_init_tab_qt1010;
		break;
	case AF9013_TUNER_MT2060_2:
		len = ARRAY_SIZE(tuner_init_tab_mt2060_2);
		tab = tuner_init_tab_mt2060_2;
		break;
	case AF9013_TUNER_TDA18271:
	case AF9013_TUNER_TDA18218:
		len = ARRAY_SIZE(tuner_init_tab_tda18271);
		tab = tuner_init_tab_tda18271;
		break;
	case AF9013_TUNER_UNKNOWN:
	default:
		len = ARRAY_SIZE(tuner_init_tab_unknown);
		tab = tuner_init_tab_unknown;
		break;
	}

	for (i = 0; i < len; i++) {
		ret = regmap_update_bits(state->regmap, tab[i].reg, tab[i].mask,
					 tab[i].val);
		if (ret)
			goto err;
	}

	/* TS interface */
	if (state->ts_output_pin == 7)
		utmp = 1 << 3 | state->ts_mode << 1;
	else
		utmp = 0 << 3 | state->ts_mode << 1;
	ret = regmap_update_bits(state->regmap, 0xd500, 0x0e, utmp);
	if (ret)
		goto err;

	/* enable lock led */
	ret = regmap_update_bits(state->regmap, 0xd730, 0x01, 0x01);
	if (ret)
		goto err;

	state->first_tune = true;

	return 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	return ret;
}