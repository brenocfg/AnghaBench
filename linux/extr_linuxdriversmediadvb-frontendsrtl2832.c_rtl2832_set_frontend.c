#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int member_15; int member_16; int member_17; int member_18; int member_19; int member_20; int member_21; int member_22; int member_23; int member_24; int member_25; int member_26; int member_27; int member_28; int member_29; int member_30; int member_31; } ;
typedef  TYPE_4__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct rtl2832_dev {TYPE_3__* pdata; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int (* get_if_frequency ) (struct dvb_frontend*,int*) ;int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_7__ {TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int bandwidth_hz; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; struct rtl2832_dev* demodulator_priv; } ;
typedef  int /*<<< orphan*/  bw_params ;
struct TYPE_8__ {unsigned long long clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVBT_CFREQ_OFF_RATIO ; 
 int /*<<< orphan*/  DVBT_RSAMP_RATIO ; 
 int /*<<< orphan*/  DVBT_SOFT_RST ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int div_u64 (int,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,TYPE_4__*,int) ; 
 int rtl2832_set_if (struct dvb_frontend*,int) ; 
 int rtl2832_wr_demod_reg (struct rtl2832_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 
 int stub2 (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int rtl2832_set_frontend(struct dvb_frontend *fe)
{
	struct rtl2832_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i, j;
	u64 bw_mode, num, num2;
	u32 resamp_ratio, cfreq_off_ratio;
	static u8 bw_params[3][32] = {
	/* 6 MHz bandwidth */
		{
		0xf5, 0xff, 0x15, 0x38, 0x5d, 0x6d, 0x52, 0x07, 0xfa, 0x2f,
		0x53, 0xf5, 0x3f, 0xca, 0x0b, 0x91, 0xea, 0x30, 0x63, 0xb2,
		0x13, 0xda, 0x0b, 0xc4, 0x18, 0x7e, 0x16, 0x66, 0x08, 0x67,
		0x19, 0xe0,
		},

	/*  7 MHz bandwidth */
		{
		0xe7, 0xcc, 0xb5, 0xba, 0xe8, 0x2f, 0x67, 0x61, 0x00, 0xaf,
		0x86, 0xf2, 0xbf, 0x59, 0x04, 0x11, 0xb6, 0x33, 0xa4, 0x30,
		0x15, 0x10, 0x0a, 0x42, 0x18, 0xf8, 0x17, 0xd9, 0x07, 0x22,
		0x19, 0x10,
		},

	/*  8 MHz bandwidth */
		{
		0x09, 0xf6, 0xd2, 0xa7, 0x9a, 0xc9, 0x27, 0x77, 0x06, 0xbf,
		0xec, 0xf4, 0x4f, 0x0b, 0xfc, 0x01, 0x63, 0x35, 0x54, 0xa7,
		0x16, 0x66, 0x08, 0xb4, 0x19, 0x6e, 0x19, 0x65, 0x05, 0xc8,
		0x19, 0xe0,
		},
	};

	dev_dbg(&client->dev, "frequency=%u bandwidth_hz=%u inversion=%u\n",
		c->frequency, c->bandwidth_hz, c->inversion);

	/* program tuner */
	if (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* If the frontend has get_if_frequency(), use it */
	if (fe->ops.tuner_ops.get_if_frequency) {
		u32 if_freq;

		ret = fe->ops.tuner_ops.get_if_frequency(fe, &if_freq);
		if (ret)
			goto err;

		ret = rtl2832_set_if(fe, if_freq);
		if (ret)
			goto err;
	}

	switch (c->bandwidth_hz) {
	case 6000000:
		i = 0;
		bw_mode = 48000000;
		break;
	case 7000000:
		i = 1;
		bw_mode = 56000000;
		break;
	case 8000000:
		i = 2;
		bw_mode = 64000000;
		break;
	default:
		dev_err(&client->dev, "invalid bandwidth_hz %u\n",
			c->bandwidth_hz);
		ret = -EINVAL;
		goto err;
	}

	for (j = 0; j < sizeof(bw_params[0]); j++) {
		ret = regmap_bulk_write(dev->regmap,
					0x11c + j, &bw_params[i][j], 1);
		if (ret)
			goto err;
	}

	/* calculate and set resample ratio
	* RSAMP_RATIO = floor(CrystalFreqHz * 7 * pow(2, 22)
	*	/ ConstWithBandwidthMode)
	*/
	num = dev->pdata->clk * 7ULL;
	num *= 0x400000;
	num = div_u64(num, bw_mode);
	resamp_ratio =  num & 0x3ffffff;
	ret = rtl2832_wr_demod_reg(dev, DVBT_RSAMP_RATIO, resamp_ratio);
	if (ret)
		goto err;

	/* calculate and set cfreq off ratio
	* CFREQ_OFF_RATIO = - floor(ConstWithBandwidthMode * pow(2, 20)
	*	/ (CrystalFreqHz * 7))
	*/
	num = bw_mode << 20;
	num2 = dev->pdata->clk * 7ULL;
	num = div_u64(num, num2);
	num = -num;
	cfreq_off_ratio = num & 0xfffff;
	ret = rtl2832_wr_demod_reg(dev, DVBT_CFREQ_OFF_RATIO, cfreq_off_ratio);
	if (ret)
		goto err;

	/* soft reset */
	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x1);
	if (ret)
		goto err;

	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x0);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}