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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct m88rs6000t_dev {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct dtv_frontend_properties {int symbol_rate; scalar_t__ delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct m88rs6000t_dev* tuner_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SYS_DVBS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int m88rs6000t_set_demod_mclk(struct dvb_frontend *fe)
{
	struct m88rs6000t_dev *dev = fe->tuner_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 reg11, reg15, reg16, reg1D, reg1E, reg1F;
	u8 N, f0 = 0, f1 = 0, f2 = 0, f3 = 0;
	u16 pll_div_fb;
	u32 div, ts_mclk;
	unsigned int utmp;
	int ret;

	/* select demod main mclk */
	ret = regmap_read(dev->regmap, 0x15, &utmp);
	if (ret)
		goto err;
	reg15 = utmp;
	if (c->symbol_rate > 45010000) {
		reg11 = 0x0E;
		reg15 |= 0x02;
		reg16 = 115; /* mclk = 110.25MHz */
	} else {
		reg11 = 0x0A;
		reg15 &= ~0x02;
		reg16 = 96; /* mclk = 96MHz */
	}

	/* set ts mclk */
	if (c->delivery_system == SYS_DVBS)
		ts_mclk = 96000;
	else
		ts_mclk = 144000;

	pll_div_fb = (reg15 & 0x01) << 8;
	pll_div_fb += reg16;
	pll_div_fb += 32;

	div = 36000 * pll_div_fb;
	div /= ts_mclk;

	if (div <= 32) {
		N = 2;
		f0 = 0;
		f1 = div / 2;
		f2 = div - f1;
		f3 = 0;
	} else if (div <= 48) {
		N = 3;
		f0 = div / 3;
		f1 = (div - f0) / 2;
		f2 = div - f0 - f1;
		f3 = 0;
	} else if (div <= 64) {
		N = 4;
		f0 = div / 4;
		f1 = (div - f0) / 3;
		f2 = (div - f0 - f1) / 2;
		f3 = div - f0 - f1 - f2;
	} else {
		N = 4;
		f0 = 16;
		f1 = 16;
		f2 = 16;
		f3 = 16;
	}

	if (f0 == 16)
		f0 = 0;
	if (f1 == 16)
		f1 = 0;
	if (f2 == 16)
		f2 = 0;
	if (f3 == 16)
		f3 = 0;

	ret = regmap_read(dev->regmap, 0x1D, &utmp);
	if (ret)
		goto err;
	reg1D = utmp;
	reg1D &= ~0x03;
	reg1D |= N - 1;
	reg1E = ((f3 << 4) + f2) & 0xFF;
	reg1F = ((f1 << 4) + f0) & 0xFF;

	/* program and recalibrate demod PLL */
	ret = regmap_write(dev->regmap, 0x05, 0x40);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x11, 0x08);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x15, reg15);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x16, reg16);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x1D, reg1D);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x1E, reg1E);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x1F, reg1F);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x17, 0xc1);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x17, 0x81);
	if (ret)
		goto err;
	usleep_range(5000, 50000);
	ret = regmap_write(dev->regmap, 0x05, 0x00);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x11, reg11);
	if (ret)
		goto err;
	usleep_range(5000, 50000);
err:
	if (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	return ret;
}