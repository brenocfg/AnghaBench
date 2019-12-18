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
struct adf4371_state {int fpfd; int ref_div_factor; int clkin_freq; unsigned int* buf; int /*<<< orphan*/  regmap; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADF4371_ADDR_ASC (int) ; 
 int ADF4371_ADDR_ASC_MSK ; 
 int ADF4371_ADDR_ASC_R (int) ; 
 int ADF4371_ADDR_ASC_R_MSK ; 
 int ADF4371_MAX_FREQ_PFD ; 
 int ADF4371_MUTE_LD (int) ; 
 int ADF4371_MUTE_LD_MSK ; 
 int /*<<< orphan*/  ADF4371_REG (int) ; 
 int /*<<< orphan*/  ADF4371_RESET_CMD ; 
 int ADF4371_TIMEOUT (unsigned int) ; 
 unsigned int ADF4371_VCO_ALC_TOUT (unsigned int) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int DIV_ROUND_CLOSEST (int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (int,unsigned int) ; 
 int /*<<< orphan*/  adf4371_reg_defaults ; 
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 
 int regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adf4371_setup(struct adf4371_state *st)
{
	unsigned int synth_timeout = 2, timeout = 1, vco_alc_timeout = 1;
	unsigned int vco_band_div, tmp;
	int ret;

	/* Perform a software reset */
	ret = regmap_write(st->regmap, ADF4371_REG(0x0), ADF4371_RESET_CMD);
	if (ret < 0)
		return ret;

	ret = regmap_multi_reg_write(st->regmap, adf4371_reg_defaults,
				     ARRAY_SIZE(adf4371_reg_defaults));
	if (ret < 0)
		return ret;

	/* Mute to Lock Detect */
	if (device_property_read_bool(&st->spi->dev, "adi,mute-till-lock-en")) {
		ret = regmap_update_bits(st->regmap, ADF4371_REG(0x25),
					 ADF4371_MUTE_LD_MSK,
					 ADF4371_MUTE_LD(1));
		if (ret < 0)
			return ret;
	}

	/* Set address in ascending order, so the bulk_write() will work */
	ret = regmap_update_bits(st->regmap, ADF4371_REG(0x0),
				 ADF4371_ADDR_ASC_MSK | ADF4371_ADDR_ASC_R_MSK,
				 ADF4371_ADDR_ASC(1) | ADF4371_ADDR_ASC_R(1));
	if (ret < 0)
		return ret;
	/*
	 * Calculate and maximize PFD frequency
	 * fPFD = REFIN × ((1 + D)/(R × (1 + T)))
	 * Where D is the REFIN doubler bit, T is the reference divide by 2,
	 * R is the reference division factor
	 * TODO: it is assumed D and T equal 0.
	 */
	do {
		st->ref_div_factor++;
		st->fpfd = st->clkin_freq / st->ref_div_factor;
	} while (st->fpfd > ADF4371_MAX_FREQ_PFD);

	/* Calculate Timeouts */
	vco_band_div = DIV_ROUND_UP(st->fpfd, 2400000U);

	tmp = DIV_ROUND_CLOSEST(st->fpfd, 1000000U);
	do {
		timeout++;
		if (timeout > 1023) {
			timeout = 2;
			synth_timeout++;
		}
	} while (synth_timeout * 1024 + timeout <= 20 * tmp);

	do {
		vco_alc_timeout++;
	} while (vco_alc_timeout * 1024 - timeout <= 50 * tmp);

	st->buf[0] = vco_band_div;
	st->buf[1] = timeout & 0xFF;
	st->buf[2] = ADF4371_TIMEOUT(timeout >> 8) | 0x04;
	st->buf[3] = synth_timeout;
	st->buf[4] = ADF4371_VCO_ALC_TOUT(vco_alc_timeout);

	return regmap_bulk_write(st->regmap, ADF4371_REG(0x30), st->buf, 5);
}