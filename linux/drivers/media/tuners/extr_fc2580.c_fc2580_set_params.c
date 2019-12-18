#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned int u64 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct fc2580_dev {scalar_t__ f_frequency; scalar_t__ f_bandwidth; int /*<<< orphan*/  regmap; scalar_t__ clk; int /*<<< orphan*/  active; struct i2c_client* client; } ;
struct TYPE_5__ {scalar_t__ freq; unsigned int div_out; int band; int r36_val; int r39_val; int /*<<< orphan*/  r6f_val; int /*<<< orphan*/  r6e_val; int /*<<< orphan*/  r6d_val; int /*<<< orphan*/  r6c_val; int /*<<< orphan*/  r6b_val; int /*<<< orphan*/  r6a_val; int /*<<< orphan*/  r69_val; int /*<<< orphan*/  r68_val; int /*<<< orphan*/  r67_val; int /*<<< orphan*/  r63_val; int /*<<< orphan*/  r62_val; int /*<<< orphan*/  r61_val; int /*<<< orphan*/  r5f_val; int /*<<< orphan*/  r53_val; int /*<<< orphan*/  r50_val; int /*<<< orphan*/  r44_val; int /*<<< orphan*/  r30_val; int /*<<< orphan*/  r2d_val; int /*<<< orphan*/  r2c_val; int /*<<< orphan*/  r2b_val; int /*<<< orphan*/  r29_val; int /*<<< orphan*/  r28_val; int /*<<< orphan*/  r27_val; int /*<<< orphan*/  r25_val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int DIV_N_MIN ; 
 unsigned int DIV_PRE_N ; 
 int EINVAL ; 
 unsigned int F_REF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int div64_u64 (unsigned int,unsigned long long) ; 
 unsigned int div_u64 (unsigned int,unsigned int) ; 
 unsigned int div_u64_rem (unsigned int,unsigned int,unsigned int*) ; 
 TYPE_1__* fc2580_freq_regs_lut ; 
 TYPE_1__* fc2580_if_filter_lut ; 
 TYPE_1__* fc2580_pll_lut ; 
 int fc2580_wr_reg_ff (struct fc2580_dev*,int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int fc2580_set_params(struct fc2580_dev *dev)
{
	struct i2c_client *client = dev->client;
	int ret, i;
	unsigned int uitmp, div_ref, div_ref_val, div_n, k, k_cw, div_out;
	u64 f_vco;
	u8 synth_config;
	unsigned long timeout;

	if (!dev->active) {
		dev_dbg(&client->dev, "tuner is sleeping\n");
		return 0;
	}

	/*
	 * Fractional-N synthesizer
	 *
	 *                      +---------------------------------------+
	 *                      v                                       |
	 *  Fref   +----+     +----+     +-------+         +----+     +------+     +---+
	 * ------> | /R | --> | PD | --> |  VCO  | ------> | /2 | --> | /N.F | <-- | K |
	 *         +----+     +----+     +-------+         +----+     +------+     +---+
	 *                                 |
	 *                                 |
	 *                                 v
	 *                               +-------+  Fout
	 *                               | /Rout | ------>
	 *                               +-------+
	 */
	for (i = 0; i < ARRAY_SIZE(fc2580_pll_lut); i++) {
		if (dev->f_frequency <= fc2580_pll_lut[i].freq)
			break;
	}
	if (i == ARRAY_SIZE(fc2580_pll_lut)) {
		ret = -EINVAL;
		goto err;
	}

	#define DIV_PRE_N 2
	#define F_REF dev->clk
	div_out = fc2580_pll_lut[i].div_out;
	f_vco = (u64) dev->f_frequency * div_out;
	synth_config = fc2580_pll_lut[i].band;
	if (f_vco < 2600000000ULL)
		synth_config |= 0x06;
	else
		synth_config |= 0x0e;

	/* select reference divider R (keep PLL div N in valid range) */
	#define DIV_N_MIN 76
	if (f_vco >= div_u64((u64) DIV_PRE_N * DIV_N_MIN * F_REF, 1)) {
		div_ref = 1;
		div_ref_val = 0x00;
	} else if (f_vco >= div_u64((u64) DIV_PRE_N * DIV_N_MIN * F_REF, 2)) {
		div_ref = 2;
		div_ref_val = 0x10;
	} else {
		div_ref = 4;
		div_ref_val = 0x20;
	}

	/* calculate PLL integer and fractional control word */
	uitmp = DIV_PRE_N * F_REF / div_ref;
	div_n = div_u64_rem(f_vco, uitmp, &k);
	k_cw = div_u64((u64) k * 0x100000, uitmp);

	dev_dbg(&client->dev,
		"frequency=%u bandwidth=%u f_vco=%llu F_REF=%u div_ref=%u div_n=%u k=%u div_out=%u k_cw=%0x\n",
		dev->f_frequency, dev->f_bandwidth, f_vco, F_REF, div_ref,
		div_n, k, div_out, k_cw);

	ret = regmap_write(dev->regmap, 0x02, synth_config);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x18, div_ref_val << 0 | k_cw >> 16);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x1a, (k_cw >> 8) & 0xff);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x1b, (k_cw >> 0) & 0xff);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x1c, div_n);
	if (ret)
		goto err;

	/* registers */
	for (i = 0; i < ARRAY_SIZE(fc2580_freq_regs_lut); i++) {
		if (dev->f_frequency <= fc2580_freq_regs_lut[i].freq)
			break;
	}
	if (i == ARRAY_SIZE(fc2580_freq_regs_lut)) {
		ret = -EINVAL;
		goto err;
	}

	ret = fc2580_wr_reg_ff(dev, 0x25, fc2580_freq_regs_lut[i].r25_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x27, fc2580_freq_regs_lut[i].r27_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x28, fc2580_freq_regs_lut[i].r28_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x29, fc2580_freq_regs_lut[i].r29_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x2b, fc2580_freq_regs_lut[i].r2b_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x2c, fc2580_freq_regs_lut[i].r2c_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x2d, fc2580_freq_regs_lut[i].r2d_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x30, fc2580_freq_regs_lut[i].r30_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x44, fc2580_freq_regs_lut[i].r44_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x50, fc2580_freq_regs_lut[i].r50_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x53, fc2580_freq_regs_lut[i].r53_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x5f, fc2580_freq_regs_lut[i].r5f_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x61, fc2580_freq_regs_lut[i].r61_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x62, fc2580_freq_regs_lut[i].r62_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x63, fc2580_freq_regs_lut[i].r63_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x67, fc2580_freq_regs_lut[i].r67_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x68, fc2580_freq_regs_lut[i].r68_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x69, fc2580_freq_regs_lut[i].r69_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x6a, fc2580_freq_regs_lut[i].r6a_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x6b, fc2580_freq_regs_lut[i].r6b_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x6c, fc2580_freq_regs_lut[i].r6c_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x6d, fc2580_freq_regs_lut[i].r6d_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x6e, fc2580_freq_regs_lut[i].r6e_val);
	if (ret)
		goto err;

	ret = fc2580_wr_reg_ff(dev, 0x6f, fc2580_freq_regs_lut[i].r6f_val);
	if (ret)
		goto err;

	/* IF filters */
	for (i = 0; i < ARRAY_SIZE(fc2580_if_filter_lut); i++) {
		if (dev->f_bandwidth <= fc2580_if_filter_lut[i].freq)
			break;
	}
	if (i == ARRAY_SIZE(fc2580_if_filter_lut)) {
		ret = -EINVAL;
		goto err;
	}

	ret = regmap_write(dev->regmap, 0x36, fc2580_if_filter_lut[i].r36_val);
	if (ret)
		goto err;

	uitmp = (unsigned int) 8058000 - (dev->f_bandwidth * 122 / 100 / 2);
	uitmp = div64_u64((u64) dev->clk * uitmp, 1000000000000ULL);
	ret = regmap_write(dev->regmap, 0x37, uitmp);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, 0x39, fc2580_if_filter_lut[i].r39_val);
	if (ret)
		goto err;

	timeout = jiffies + msecs_to_jiffies(30);
	for (uitmp = ~0xc0; !time_after(jiffies, timeout) && uitmp != 0xc0;) {
		/* trigger filter */
		ret = regmap_write(dev->regmap, 0x2e, 0x09);
		if (ret)
			goto err;

		/* locked when [7:6] are set (val: d7 6MHz, d5 7MHz, cd 8MHz) */
		ret = regmap_read(dev->regmap, 0x2f, &uitmp);
		if (ret)
			goto err;
		uitmp &= 0xc0;

		ret = regmap_write(dev->regmap, 0x2e, 0x01);
		if (ret)
			goto err;
	}
	if (uitmp != 0xc0)
		dev_dbg(&client->dev, "filter did not lock %02x\n", uitmp);

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}