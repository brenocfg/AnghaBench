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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct tda18250_dev {scalar_t__ if_atsc; scalar_t__ if_dvbt_6; scalar_t__ if_dvbt_7; scalar_t__ if_dvbt_8; scalar_t__ if_dvbc_6; scalar_t__ if_dvbc_8; scalar_t__ if_frequency; int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dtv_frontend_properties {int delivery_system; int frequency; int bandwidth_hz; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct i2c_client* tuner_priv; } ;

/* Variables and functions */
#define  ATSC 140 
 size_t DIV_ROUND_CLOSEST (scalar_t__,int) ; 
#define  DVBC_6 139 
#define  DVBC_8 138 
#define  DVBT_6 137 
#define  DVBT_7 136 
#define  DVBT_8 135 
 int EINVAL ; 
#define  MASK 134 
 size_t const R0A_IRQ3 ; 
 size_t const R14_AGC23 ; 
 size_t const R1A_AGCK ; 
 size_t const R26_IF ; 
 int /*<<< orphan*/  R27_RF1 ; 
 size_t const R2A_MSM1 ; 
 size_t const R2B_MSM2 ; 
 size_t const R39_SD5 ; 
 size_t const R46_CPUMP ; 
 size_t const R4F_XTALFLX3 ; 
#define  REG 133 
#define  SYS_ATSC 132 
#define  SYS_DVBC_ANNEX_A 131 
#define  SYS_DVBC_ANNEX_C 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int TDA18250_IRQ_TUNE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct tda18250_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,size_t const,int) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,size_t const,size_t const,size_t const) ; 
 int tda18250_pll_calc (struct dvb_frontend*,size_t*,size_t*,size_t*) ; 
 int tda18250_set_agc (struct dvb_frontend*) ; 
 int tda18250_wait_for_irq (struct dvb_frontend*,int,int,int) ; 

__attribute__((used)) static int tda18250_set_params(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->tuner_priv;
	struct tda18250_dev *dev = i2c_get_clientdata(client);
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 if_khz;
	int ret;
	unsigned int i, j;
	u8 utmp;
	u8 buf[3];

	#define REG      0
	#define MASK     1
	#define DVBT_6   2
	#define DVBT_7   3
	#define DVBT_8   4
	#define DVBC_6   5
	#define DVBC_8   6
	#define ATSC     7

	static const u8 delsys_params[][16] = {
		[REG]    = { 0x22, 0x23, 0x24, 0x21, 0x0d, 0x0c, 0x0f, 0x14,
			     0x0e, 0x12, 0x58, 0x59, 0x1a, 0x19, 0x1e, 0x30 },
		[MASK]   = { 0x77, 0xff, 0xff, 0x87, 0xf0, 0x78, 0x07, 0xe0,
			     0x60, 0x0f, 0x60, 0x0f, 0x33, 0x30, 0x80, 0x06 },
		[DVBT_6] = { 0x51, 0x03, 0x83, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x60, 0x0f, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 },
		[DVBT_7] = { 0x52, 0x03, 0x85, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x60, 0x0f, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 },
		[DVBT_8] = { 0x53, 0x03, 0x87, 0x82, 0x40, 0x48, 0x06, 0xe0,
			     0x60, 0x07, 0x60, 0x05, 0x03, 0x10, 0x00, 0x04 },
		[DVBC_6] = { 0x32, 0x05, 0x86, 0x82, 0x50, 0x00, 0x06, 0x60,
			     0x40, 0x0e, 0x60, 0x05, 0x33, 0x10, 0x00, 0x04 },
		[DVBC_8] = { 0x53, 0x03, 0x88, 0x82, 0x50, 0x00, 0x06, 0x60,
			     0x40, 0x0e, 0x60, 0x05, 0x33, 0x10, 0x00, 0x04 },
		[ATSC]   = { 0x51, 0x03, 0x83, 0x82, 0x40, 0x48, 0x01, 0xe0,
			     0x40, 0x0e, 0x60, 0x05, 0x03, 0x00, 0x80, 0x04 },
	};

	dev_dbg(&client->dev,
			"delivery_system=%d frequency=%u bandwidth_hz=%u",
			c->delivery_system, c->frequency, c->bandwidth_hz);


	switch (c->delivery_system) {
	case SYS_ATSC:
		j = ATSC;
		if_khz = dev->if_atsc;
		break;
	case SYS_DVBT:
	case SYS_DVBT2:
		if (c->bandwidth_hz == 0) {
			ret = -EINVAL;
			goto err;
		} else if (c->bandwidth_hz <= 6000000) {
			j = DVBT_6;
			if_khz = dev->if_dvbt_6;
		} else if (c->bandwidth_hz <= 7000000) {
			j = DVBT_7;
			if_khz = dev->if_dvbt_7;
		} else if (c->bandwidth_hz <= 8000000) {
			j = DVBT_8;
			if_khz = dev->if_dvbt_8;
		} else {
			ret = -EINVAL;
			goto err;
		}
		break;
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		if (c->bandwidth_hz == 0) {
			ret = -EINVAL;
			goto err;
		} else if (c->bandwidth_hz <= 6000000) {
			j = DVBC_6;
			if_khz = dev->if_dvbc_6;
		} else if (c->bandwidth_hz <= 8000000) {
			j = DVBC_8;
			if_khz = dev->if_dvbc_8;
		} else {
			ret = -EINVAL;
			goto err;
		}
		break;
	default:
		ret = -EINVAL;
		dev_err(&client->dev, "unsupported delivery system=%d",
				c->delivery_system);
		goto err;
	}

	/* set delivery system dependent registers */
	for (i = 0; i < 16; i++) {
		ret = regmap_write_bits(dev->regmap, delsys_params[REG][i],
			 delsys_params[MASK][i],  delsys_params[j][i]);
		if (ret)
			goto err;
	}

	/* set IF if needed */
	if (dev->if_frequency != if_khz) {
		utmp = DIV_ROUND_CLOSEST(if_khz, 50);
		ret = regmap_write(dev->regmap, R26_IF, utmp);
		if (ret)
			goto err;
		dev->if_frequency = if_khz;
		dev_dbg(&client->dev, "set IF=%u kHz", if_khz);

	}

	ret = tda18250_set_agc(fe);
	if (ret)
		goto err;

	ret = regmap_write_bits(dev->regmap, R1A_AGCK, 0x03, 0x01);
	if (ret)
		goto err;

	ret = regmap_write_bits(dev->regmap, R14_AGC23, 0x40, 0x00);
	if (ret)
		goto err;

	/* set frequency */
	buf[0] = ((c->frequency / 1000) >> 16) & 0xff;
	buf[1] = ((c->frequency / 1000) >>  8) & 0xff;
	buf[2] = ((c->frequency / 1000) >>  0) & 0xff;
	ret = regmap_bulk_write(dev->regmap, R27_RF1, buf, 3);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, R0A_IRQ3, TDA18250_IRQ_TUNE);
	if (ret)
		goto err;

	/* initial tune */
	ret = regmap_write(dev->regmap, R2A_MSM1, 0x01);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, R2B_MSM2, 0x01);
	if (ret)
		goto err;

	ret = tda18250_wait_for_irq(fe, 500, 10, TDA18250_IRQ_TUNE);
	if (ret)
		goto err;

	/* calc ndiv and rdiv */
	ret = tda18250_pll_calc(fe, &buf[0], &buf[1], &buf[2]);
	if (ret)
		goto err;

	ret = regmap_write_bits(dev->regmap, R4F_XTALFLX3, 0xe0,
			(buf[0] << 6) | (buf[1] << 5));
	if (ret)
		goto err;

	/* clear IRQ */
	ret = regmap_write(dev->regmap, R0A_IRQ3, TDA18250_IRQ_TUNE);
	if (ret)
		goto err;

	ret = regmap_write_bits(dev->regmap, R46_CPUMP, 0x07, 0x00);
	if (ret)
		goto err;

	ret = regmap_write_bits(dev->regmap, R39_SD5, 0x03, 0x00);
	if (ret)
		goto err;

	/* tune again */
	ret = regmap_write(dev->regmap, R2A_MSM1, 0x01); /* tune */
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, R2B_MSM2, 0x01); /* go */
	if (ret)
		goto err;

	ret = tda18250_wait_for_irq(fe, 500, 10, TDA18250_IRQ_TUNE);
	if (ret)
		goto err;

	/* pll locking */
	msleep(20);

	ret = regmap_write_bits(dev->regmap, R2B_MSM2, 0x04, 0x04);
	if (ret)
		goto err;

	msleep(20);

	/* restore AGCK */
	ret = regmap_write_bits(dev->regmap, R1A_AGCK, 0x03, 0x03);
	if (ret)
		goto err;

	ret = regmap_write_bits(dev->regmap, R14_AGC23, 0x40, 0x40);
	if (ret)
		goto err;

	/* charge pump */
	ret = regmap_write_bits(dev->regmap, R46_CPUMP, 0x07, buf[2]);

	return 0;
err:
	return ret;
}