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
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct it913x_dev {int fn_min; scalar_t__ clk_mode; int fdiv; unsigned int xtal; int /*<<< orphan*/  regmap; int /*<<< orphan*/  active; int /*<<< orphan*/  role; struct platform_device* pdev; } ;
struct dtv_frontend_properties {int frequency; int bandwidth_hz; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct it913x_dev* tuner_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int it913x_set_params(struct dvb_frontend *fe)
{
	struct it913x_dev *dev = fe->tuner_priv;
	struct platform_device *pdev = dev->pdev;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret;
	unsigned int utmp;
	u32 pre_lo_freq, t_cal_freq;
	u16 iqik_m_cal, n_div;
	u8 u8tmp, n, l_band, lna_band;

	dev_dbg(&pdev->dev, "role=%u, frequency %u, bandwidth_hz %u\n",
			dev->role, c->frequency, c->bandwidth_hz);

	if (!dev->active) {
		ret = -EINVAL;
		goto err;
	}

	if (c->frequency <=         74000000) {
		n_div = 48;
		n = 0;
	} else if (c->frequency <= 111000000) {
		n_div = 32;
		n = 1;
	} else if (c->frequency <= 148000000) {
		n_div = 24;
		n = 2;
	} else if (c->frequency <= 222000000) {
		n_div = 16;
		n = 3;
	} else if (c->frequency <= 296000000) {
		n_div = 12;
		n = 4;
	} else if (c->frequency <= 445000000) {
		n_div = 8;
		n = 5;
	} else if (c->frequency <= dev->fn_min) {
		n_div = 6;
		n = 6;
	} else if (c->frequency <= 950000000) {
		n_div = 4;
		n = 7;
	} else {
		n_div = 2;
		n = 0;
	}

	ret = regmap_read(dev->regmap, 0x80ed81, &utmp);
	if (ret)
		goto err;

	iqik_m_cal = utmp * n_div;

	if (utmp < 0x20) {
		if (dev->clk_mode == 0)
			iqik_m_cal = (iqik_m_cal * 9) >> 5;
		else
			iqik_m_cal >>= 1;
	} else {
		iqik_m_cal = 0x40 - iqik_m_cal;
		if (dev->clk_mode == 0)
			iqik_m_cal = ~((iqik_m_cal * 9) >> 5);
		else
			iqik_m_cal = ~(iqik_m_cal >> 1);
	}

	t_cal_freq = (c->frequency / 1000) * n_div * dev->fdiv;
	pre_lo_freq = t_cal_freq / dev->xtal;
	utmp = pre_lo_freq * dev->xtal;

	if ((t_cal_freq - utmp) >= (dev->xtal >> 1))
		pre_lo_freq++;

	pre_lo_freq += (u32) n << 13;
	/* Frequency OMEGA_IQIK_M_CAL_MID*/
	t_cal_freq = pre_lo_freq + (u32)iqik_m_cal;
	dev_dbg(&pdev->dev, "t_cal_freq %u, pre_lo_freq %u\n",
			t_cal_freq, pre_lo_freq);

	if (c->frequency <=         440000000) {
		l_band = 0;
		lna_band = 0;
	} else if (c->frequency <=  484000000) {
		l_band = 1;
		lna_band = 1;
	} else if (c->frequency <=  533000000) {
		l_band = 1;
		lna_band = 2;
	} else if (c->frequency <=  587000000) {
		l_band = 1;
		lna_band = 3;
	} else if (c->frequency <=  645000000) {
		l_band = 1;
		lna_band = 4;
	} else if (c->frequency <=  710000000) {
		l_band = 1;
		lna_band = 5;
	} else if (c->frequency <=  782000000) {
		l_band = 1;
		lna_band = 6;
	} else if (c->frequency <=  860000000) {
		l_band = 1;
		lna_band = 7;
	} else if (c->frequency <= 1492000000) {
		l_band = 1;
		lna_band = 0;
	} else if (c->frequency <= 1685000000) {
		l_band = 1;
		lna_band = 1;
	} else {
		ret = -EINVAL;
		goto err;
	}

	/* XXX: latest windows driver does not set that at all */
	ret = regmap_write(dev->regmap, 0x80ee06, lna_band);
	if (ret)
		goto err;

	if (c->bandwidth_hz <=      5000000)
		u8tmp = 0;
	else if (c->bandwidth_hz <= 6000000)
		u8tmp = 2;
	else if (c->bandwidth_hz <= 7000000)
		u8tmp = 4;
	else
		u8tmp = 6;       /* 8000000 */

	ret = regmap_write(dev->regmap, 0x80ec56, u8tmp);
	if (ret)
		goto err;

	/* XXX: latest windows driver sets different value (a8 != 68) */
	ret = regmap_write(dev->regmap, 0x80ec4c, 0xa0 | (l_band << 3));
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x80ec4d, (t_cal_freq >> 0) & 0xff);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x80ec4e, (t_cal_freq >> 8) & 0xff);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x80011e, (pre_lo_freq >> 0) & 0xff);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x80011f, (pre_lo_freq >> 8) & 0xff);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&pdev->dev, "failed %d\n", ret);
	return ret;
}