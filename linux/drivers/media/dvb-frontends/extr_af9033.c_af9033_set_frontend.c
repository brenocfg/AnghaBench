#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_if_frequency ) (struct dvb_frontend*,scalar_t__*) ;int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_8__ {TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int frequency; int bandwidth_hz; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; struct af9033_dev* demodulator_priv; } ;
struct TYPE_9__ {scalar_t__ clock; scalar_t__ adc_multiplier; int /*<<< orphan*/  spec_inv; } ;
struct af9033_dev {int bandwidth_hz; int /*<<< orphan*/  regmap; TYPE_3__ cfg; struct i2c_client* client; } ;
struct TYPE_10__ {scalar_t__ clock; int bandwidth_hz; int* val; unsigned int adc; } ;

/* Variables and functions */
 scalar_t__ AF9033_ADC_MULTIPLIER_2X ; 
 int ARRAY_SIZE (TYPE_4__*) ; 
 unsigned int DIV_ROUND_CLOSEST_ULL (int,unsigned int) ; 
 int EINVAL ; 
 TYPE_4__* clock_adc_lut ; 
 TYPE_4__* coeff_lut ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,scalar_t__*) ; 

__attribute__((used)) static int af9033_set_frontend(struct dvb_frontend *fe)
{
	struct af9033_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i;
	unsigned int utmp, adc_freq;
	u8 tmp, buf[3], bandwidth_reg_val;
	u32 if_frequency;

	dev_dbg(&client->dev, "frequency=%u bandwidth_hz=%u\n",
		c->frequency, c->bandwidth_hz);

	/* Check bandwidth */
	switch (c->bandwidth_hz) {
	case 6000000:
		bandwidth_reg_val = 0x00;
		break;
	case 7000000:
		bandwidth_reg_val = 0x01;
		break;
	case 8000000:
		bandwidth_reg_val = 0x02;
		break;
	default:
		dev_dbg(&client->dev, "invalid bandwidth_hz\n");
		ret = -EINVAL;
		goto err;
	}

	/* Program tuner */
	if (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* Coefficients */
	if (c->bandwidth_hz != dev->bandwidth_hz) {
		for (i = 0; i < ARRAY_SIZE(coeff_lut); i++) {
			if (coeff_lut[i].clock == dev->cfg.clock &&
			    coeff_lut[i].bandwidth_hz == c->bandwidth_hz) {
				break;
			}
		}
		if (i == ARRAY_SIZE(coeff_lut)) {
			dev_err(&client->dev,
				"Couldn't find config for clock %u\n",
				dev->cfg.clock);
			ret = -EINVAL;
			goto err;
		}

		ret = regmap_bulk_write(dev->regmap, 0x800001, coeff_lut[i].val,
					sizeof(coeff_lut[i].val));
		if (ret)
			goto err;
	}

	/* IF frequency control */
	if (c->bandwidth_hz != dev->bandwidth_hz) {
		for (i = 0; i < ARRAY_SIZE(clock_adc_lut); i++) {
			if (clock_adc_lut[i].clock == dev->cfg.clock)
				break;
		}
		if (i == ARRAY_SIZE(clock_adc_lut)) {
			dev_err(&client->dev,
				"Couldn't find ADC clock for clock %u\n",
				dev->cfg.clock);
			ret = -EINVAL;
			goto err;
		}
		adc_freq = clock_adc_lut[i].adc;

		if (dev->cfg.adc_multiplier == AF9033_ADC_MULTIPLIER_2X)
			adc_freq = 2 * adc_freq;

		/* Get used IF frequency */
		if (fe->ops.tuner_ops.get_if_frequency)
			fe->ops.tuner_ops.get_if_frequency(fe, &if_frequency);
		else
			if_frequency = 0;

		utmp = DIV_ROUND_CLOSEST_ULL((u64)if_frequency * 0x800000,
					     adc_freq);

		if (!dev->cfg.spec_inv && if_frequency)
			utmp = 0x800000 - utmp;

		buf[0] = (utmp >>  0) & 0xff;
		buf[1] = (utmp >>  8) & 0xff;
		buf[2] = (utmp >> 16) & 0xff;
		ret = regmap_bulk_write(dev->regmap, 0x800029, buf, 3);
		if (ret)
			goto err;

		dev_dbg(&client->dev, "if_frequency_cw=%06x\n", utmp);

		dev->bandwidth_hz = c->bandwidth_hz;
	}

	ret = regmap_update_bits(dev->regmap, 0x80f904, 0x03,
				 bandwidth_reg_val);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x800040, 0x00);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x800047, 0x00);
	if (ret)
		goto err;
	ret = regmap_update_bits(dev->regmap, 0x80f999, 0x01, 0x00);
	if (ret)
		goto err;

	if (c->frequency <= 230000000)
		tmp = 0x00; /* VHF */
	else
		tmp = 0x01; /* UHF */

	ret = regmap_write(dev->regmap, 0x80004b, tmp);
	if (ret)
		goto err;
	/* Reset FSM */
	ret = regmap_write(dev->regmap, 0x800000, 0x00);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}