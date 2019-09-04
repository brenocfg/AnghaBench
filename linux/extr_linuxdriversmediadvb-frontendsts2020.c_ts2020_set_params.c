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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ts2020_priv {unsigned int frequency_div; unsigned int frequency_khz; scalar_t__ tuner; int /*<<< orphan*/  regmap; } ;
struct dtv_frontend_properties {unsigned int frequency; int bandwidth_hz; } ;
struct dvb_frontend {struct ts2020_priv* tuner_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ FREQ_OFFSET_LOW_SYM_RATE ; 
 scalar_t__ TS2020_M88TS2020 ; 
 scalar_t__ TS2020_M88TS2022 ; 
 int TS2020_XTAL_FREQ ; 
 int clamp (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int ts2020_set_tuner_rf (struct dvb_frontend*) ; 
 int ts2020_tuner_gate_ctrl (struct dvb_frontend*,int) ; 

__attribute__((used)) static int ts2020_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct ts2020_priv *priv = fe->tuner_priv;
	int ret;
	unsigned int utmp;
	u32 f3db, gdiv28;
	u16 u16tmp, value, lpf_coeff;
	u8 buf[3], reg10, lpf_mxdiv, mlpf_max, mlpf_min, nlpf;
	unsigned int f_ref_khz, f_vco_khz, div_ref, div_out, pll_n;
	unsigned int frequency_khz = c->frequency;

	/*
	 * Integer-N PLL synthesizer
	 * kHz is used for all calculations to keep calculations within 32-bit
	 */
	f_ref_khz = TS2020_XTAL_FREQ;
	div_ref = DIV_ROUND_CLOSEST(f_ref_khz, 2000);

	/* select LO output divider */
	if (frequency_khz < priv->frequency_div) {
		div_out = 4;
		reg10 = 0x10;
	} else {
		div_out = 2;
		reg10 = 0x00;
	}

	f_vco_khz = frequency_khz * div_out;
	pll_n = f_vco_khz * div_ref / f_ref_khz;
	pll_n += pll_n % 2;
	priv->frequency_khz = pll_n * f_ref_khz / div_ref / div_out;

	pr_debug("frequency=%u offset=%d f_vco_khz=%u pll_n=%u div_ref=%u div_out=%u\n",
		 priv->frequency_khz, priv->frequency_khz - c->frequency,
		 f_vco_khz, pll_n, div_ref, div_out);

	if (priv->tuner == TS2020_M88TS2020) {
		lpf_coeff = 2766;
		reg10 |= 0x01;
		ret = regmap_write(priv->regmap, 0x10, reg10);
	} else {
		lpf_coeff = 3200;
		reg10 |= 0x0b;
		ret = regmap_write(priv->regmap, 0x10, reg10);
		ret |= regmap_write(priv->regmap, 0x11, 0x40);
	}

	u16tmp = pll_n - 1024;
	buf[0] = (u16tmp >> 8) & 0xff;
	buf[1] = (u16tmp >> 0) & 0xff;
	buf[2] = div_ref - 8;

	ret |= regmap_write(priv->regmap, 0x01, buf[0]);
	ret |= regmap_write(priv->regmap, 0x02, buf[1]);
	ret |= regmap_write(priv->regmap, 0x03, buf[2]);

	ret |= ts2020_tuner_gate_ctrl(fe, 0x10);
	if (ret < 0)
		return -ENODEV;

	ret |= ts2020_tuner_gate_ctrl(fe, 0x08);

	/* Tuner RF */
	if (priv->tuner == TS2020_M88TS2020)
		ret |= ts2020_set_tuner_rf(fe);

	gdiv28 = (TS2020_XTAL_FREQ / 1000 * 1694 + 500) / 1000;
	ret |= regmap_write(priv->regmap, 0x04, gdiv28 & 0xff);
	ret |= ts2020_tuner_gate_ctrl(fe, 0x04);
	if (ret < 0)
		return -ENODEV;

	if (priv->tuner == TS2020_M88TS2022) {
		ret = regmap_write(priv->regmap, 0x25, 0x00);
		ret |= regmap_write(priv->regmap, 0x27, 0x70);
		ret |= regmap_write(priv->regmap, 0x41, 0x09);
		ret |= regmap_write(priv->regmap, 0x08, 0x0b);
		if (ret < 0)
			return -ENODEV;
	}

	regmap_read(priv->regmap, 0x26, &utmp);
	value = utmp;

	f3db = (c->bandwidth_hz / 1000 / 2) + 2000;
	f3db += FREQ_OFFSET_LOW_SYM_RATE; /* FIXME: ~always too wide filter */
	f3db = clamp(f3db, 7000U, 40000U);

	gdiv28 = gdiv28 * 207 / (value * 2 + 151);
	mlpf_max = gdiv28 * 135 / 100;
	mlpf_min = gdiv28 * 78 / 100;
	if (mlpf_max > 63)
		mlpf_max = 63;

	nlpf = (f3db * gdiv28 * 2 / lpf_coeff /
		(TS2020_XTAL_FREQ / 1000)  + 1) / 2;
	if (nlpf > 23)
		nlpf = 23;
	if (nlpf < 1)
		nlpf = 1;

	lpf_mxdiv = (nlpf * (TS2020_XTAL_FREQ / 1000)
		* lpf_coeff * 2  / f3db + 1) / 2;

	if (lpf_mxdiv < mlpf_min) {
		nlpf++;
		lpf_mxdiv = (nlpf * (TS2020_XTAL_FREQ / 1000)
			* lpf_coeff * 2  / f3db + 1) / 2;
	}

	if (lpf_mxdiv > mlpf_max)
		lpf_mxdiv = mlpf_max;

	ret = regmap_write(priv->regmap, 0x04, lpf_mxdiv);
	ret |= regmap_write(priv->regmap, 0x06, nlpf);

	ret |= ts2020_tuner_gate_ctrl(fe, 0x04);

	ret |= ts2020_tuner_gate_ctrl(fe, 0x01);

	msleep(80);

	return (ret < 0) ? -EINVAL : 0;
}