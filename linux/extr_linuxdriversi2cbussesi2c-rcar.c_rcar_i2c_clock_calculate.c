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
typedef  unsigned int u32 ;
struct rcar_i2c_priv {int devtype; unsigned int icccr; int /*<<< orphan*/  clk; } ;
struct i2c_timings {int bus_freq_hz; int scl_fall_ns; int scl_rise_ns; int scl_int_delay_ns; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
#define  I2C_RCAR_GEN1 130 
#define  I2C_RCAR_GEN2 129 
#define  I2C_RCAR_GEN3 128 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int,unsigned long,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* rcar_i2c_priv_to_dev (struct rcar_i2c_priv*) ; 

__attribute__((used)) static int rcar_i2c_clock_calculate(struct rcar_i2c_priv *priv, struct i2c_timings *t)
{
	u32 scgd, cdf, round, ick, sum, scl, cdf_width;
	unsigned long rate;
	struct device *dev = rcar_i2c_priv_to_dev(priv);

	/* Fall back to previously used values if not supplied */
	t->bus_freq_hz = t->bus_freq_hz ?: 100000;
	t->scl_fall_ns = t->scl_fall_ns ?: 35;
	t->scl_rise_ns = t->scl_rise_ns ?: 200;
	t->scl_int_delay_ns = t->scl_int_delay_ns ?: 50;

	switch (priv->devtype) {
	case I2C_RCAR_GEN1:
		cdf_width = 2;
		break;
	case I2C_RCAR_GEN2:
	case I2C_RCAR_GEN3:
		cdf_width = 3;
		break;
	default:
		dev_err(dev, "device type error\n");
		return -EIO;
	}

	/*
	 * calculate SCL clock
	 * see
	 *	ICCCR
	 *
	 * ick	= clkp / (1 + CDF)
	 * SCL	= ick / (20 + SCGD * 8 + F[(ticf + tr + intd) * ick])
	 *
	 * ick  : I2C internal clock < 20 MHz
	 * ticf : I2C SCL falling time
	 * tr   : I2C SCL rising  time
	 * intd : LSI internal delay
	 * clkp : peripheral_clk
	 * F[]  : integer up-valuation
	 */
	rate = clk_get_rate(priv->clk);
	cdf = rate / 20000000;
	if (cdf >= 1U << cdf_width) {
		dev_err(dev, "Input clock %lu too high\n", rate);
		return -EIO;
	}
	ick = rate / (cdf + 1);

	/*
	 * it is impossible to calculate large scale
	 * number on u32. separate it
	 *
	 * F[(ticf + tr + intd) * ick] with sum = (ticf + tr + intd)
	 *  = F[sum * ick / 1000000000]
	 *  = F[(ick / 1000000) * sum / 1000]
	 */
	sum = t->scl_fall_ns + t->scl_rise_ns + t->scl_int_delay_ns;
	round = (ick + 500000) / 1000000 * sum;
	round = (round + 500) / 1000;

	/*
	 * SCL	= ick / (20 + SCGD * 8 + F[(ticf + tr + intd) * ick])
	 *
	 * Calculation result (= SCL) should be less than
	 * bus_speed for hardware safety
	 *
	 * We could use something along the lines of
	 *	div = ick / (bus_speed + 1) + 1;
	 *	scgd = (div - 20 - round + 7) / 8;
	 *	scl = ick / (20 + (scgd * 8) + round);
	 * (not fully verified) but that would get pretty involved
	 */
	for (scgd = 0; scgd < 0x40; scgd++) {
		scl = ick / (20 + (scgd * 8) + round);
		if (scl <= t->bus_freq_hz)
			goto scgd_find;
	}
	dev_err(dev, "it is impossible to calculate best SCL\n");
	return -EIO;

scgd_find:
	dev_dbg(dev, "clk %d/%d(%lu), round %u, CDF:0x%x, SCGD: 0x%x\n",
		scl, t->bus_freq_hz, clk_get_rate(priv->clk), round, cdf, scgd);

	/* keep icccr value */
	priv->icccr = scgd << cdf_width | cdf;

	return 0;
}