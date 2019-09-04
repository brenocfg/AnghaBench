#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned int u64 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct e4000_dev {scalar_t__ f_frequency; scalar_t__ f_bandwidth; int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk; int /*<<< orphan*/  active; struct i2c_client* client; } ;
struct TYPE_6__ {scalar_t__ freq; unsigned int div_out; int div_out_reg; int val; int reg11_val; int reg12_val; int reg07_val; int reg78_val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int div_u64 (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int div_u64_rem (unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_1__* e4000_band_lut ; 
 TYPE_1__* e4000_if_filter_lut ; 
 TYPE_1__* e4000_pll_lut ; 
 TYPE_1__* e400_lna_filter_lut ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,...) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static int e4000_set_params(struct e4000_dev *dev)
{
	struct i2c_client *client = dev->client;
	int ret, i;
	unsigned int div_n, k, k_cw, div_out;
	u64 f_vco;
	u8 buf[5], i_data[4], q_data[4];

	if (!dev->active) {
		dev_dbg(&client->dev, "tuner is sleeping\n");
		return 0;
	}

	/* gain control manual */
	ret = regmap_write(dev->regmap, 0x1a, 0x00);
	if (ret)
		goto err;

	/*
	 * Fractional-N synthesizer
	 *
	 *           +----------------------------+
	 *           v                            |
	 *  Fref   +----+     +-------+         +------+     +---+
	 * ------> | PD | --> |  VCO  | ------> | /N.F | <-- | K |
	 *         +----+     +-------+         +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+  Fout
	 *                    | /Rout | ------>
	 *                    +-------+
	 */
	for (i = 0; i < ARRAY_SIZE(e4000_pll_lut); i++) {
		if (dev->f_frequency <= e4000_pll_lut[i].freq)
			break;
	}
	if (i == ARRAY_SIZE(e4000_pll_lut)) {
		ret = -EINVAL;
		goto err;
	}

	#define F_REF dev->clk
	div_out = e4000_pll_lut[i].div_out;
	f_vco = (u64) dev->f_frequency * div_out;
	/* calculate PLL integer and fractional control word */
	div_n = div_u64_rem(f_vco, F_REF, &k);
	k_cw = div_u64((u64) k * 0x10000, F_REF);

	dev_dbg(&client->dev,
		"frequency=%u bandwidth=%u f_vco=%llu F_REF=%u div_n=%u k=%u k_cw=%04x div_out=%u\n",
		dev->f_frequency, dev->f_bandwidth, f_vco, F_REF, div_n, k,
		k_cw, div_out);

	buf[0] = div_n;
	buf[1] = (k_cw >> 0) & 0xff;
	buf[2] = (k_cw >> 8) & 0xff;
	buf[3] = 0x00;
	buf[4] = e4000_pll_lut[i].div_out_reg;
	ret = regmap_bulk_write(dev->regmap, 0x09, buf, 5);
	if (ret)
		goto err;

	/* LNA filter (RF filter) */
	for (i = 0; i < ARRAY_SIZE(e400_lna_filter_lut); i++) {
		if (dev->f_frequency <= e400_lna_filter_lut[i].freq)
			break;
	}
	if (i == ARRAY_SIZE(e400_lna_filter_lut)) {
		ret = -EINVAL;
		goto err;
	}

	ret = regmap_write(dev->regmap, 0x10, e400_lna_filter_lut[i].val);
	if (ret)
		goto err;

	/* IF filters */
	for (i = 0; i < ARRAY_SIZE(e4000_if_filter_lut); i++) {
		if (dev->f_bandwidth <= e4000_if_filter_lut[i].freq)
			break;
	}
	if (i == ARRAY_SIZE(e4000_if_filter_lut)) {
		ret = -EINVAL;
		goto err;
	}

	buf[0] = e4000_if_filter_lut[i].reg11_val;
	buf[1] = e4000_if_filter_lut[i].reg12_val;

	ret = regmap_bulk_write(dev->regmap, 0x11, buf, 2);
	if (ret)
		goto err;

	/* frequency band */
	for (i = 0; i < ARRAY_SIZE(e4000_band_lut); i++) {
		if (dev->f_frequency <= e4000_band_lut[i].freq)
			break;
	}
	if (i == ARRAY_SIZE(e4000_band_lut)) {
		ret = -EINVAL;
		goto err;
	}

	ret = regmap_write(dev->regmap, 0x07, e4000_band_lut[i].reg07_val);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x78, e4000_band_lut[i].reg78_val);
	if (ret)
		goto err;

	/* DC offset */
	for (i = 0; i < 4; i++) {
		if (i == 0)
			ret = regmap_bulk_write(dev->regmap, 0x15, "\x00\x7e\x24", 3);
		else if (i == 1)
			ret = regmap_bulk_write(dev->regmap, 0x15, "\x00\x7f", 2);
		else if (i == 2)
			ret = regmap_bulk_write(dev->regmap, 0x15, "\x01", 1);
		else
			ret = regmap_bulk_write(dev->regmap, 0x16, "\x7e", 1);

		if (ret)
			goto err;

		ret = regmap_write(dev->regmap, 0x29, 0x01);
		if (ret)
			goto err;

		ret = regmap_bulk_read(dev->regmap, 0x2a, buf, 3);
		if (ret)
			goto err;

		i_data[i] = (((buf[2] >> 0) & 0x3) << 6) | (buf[0] & 0x3f);
		q_data[i] = (((buf[2] >> 4) & 0x3) << 6) | (buf[1] & 0x3f);
	}

	swap(q_data[2], q_data[3]);
	swap(i_data[2], i_data[3]);

	ret = regmap_bulk_write(dev->regmap, 0x50, q_data, 4);
	if (ret)
		goto err;

	ret = regmap_bulk_write(dev->regmap, 0x60, i_data, 4);
	if (ret)
		goto err;

	/* gain control auto */
	ret = regmap_write(dev->regmap, 0x1a, 0x17);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}