#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ad7768_state {int /*<<< orphan*/  mclk_freq; void* samp_freq; } ;
struct TYPE_3__ {int clk_div; int /*<<< orphan*/  dec_rate; int /*<<< orphan*/  pwrmode; int /*<<< orphan*/  mclk_div; } ;

/* Variables and functions */
 unsigned int AD7768_PWR_MCLK_DIV (int /*<<< orphan*/ ) ; 
 unsigned int AD7768_PWR_PWRMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD7768_REG_POWER_CLOCK ; 
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 void* DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int U32_MAX ; 
 unsigned int abs (int) ; 
 TYPE_1__* ad7768_clk_config ; 
 int ad7768_set_dig_fil (struct ad7768_state*,int /*<<< orphan*/ ) ; 
 int ad7768_spi_reg_write (struct ad7768_state*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ad7768_set_freq(struct ad7768_state *st,
			   unsigned int freq)
{
	unsigned int diff_new, diff_old, pwr_mode, i, idx;
	int res, ret;

	diff_old = U32_MAX;
	idx = 0;

	res = DIV_ROUND_CLOSEST(st->mclk_freq, freq);

	/* Find the closest match for the desired sampling frequency */
	for (i = 0; i < ARRAY_SIZE(ad7768_clk_config); i++) {
		diff_new = abs(res - ad7768_clk_config[i].clk_div);
		if (diff_new < diff_old) {
			diff_old = diff_new;
			idx = i;
		}
	}

	/*
	 * Set both the mclk_div and pwrmode with a single write to the
	 * POWER_CLOCK register
	 */
	pwr_mode = AD7768_PWR_MCLK_DIV(ad7768_clk_config[idx].mclk_div) |
		   AD7768_PWR_PWRMODE(ad7768_clk_config[idx].pwrmode);
	ret = ad7768_spi_reg_write(st, AD7768_REG_POWER_CLOCK, pwr_mode);
	if (ret < 0)
		return ret;

	ret =  ad7768_set_dig_fil(st, ad7768_clk_config[idx].dec_rate);
	if (ret < 0)
		return ret;

	st->samp_freq = DIV_ROUND_CLOSEST(st->mclk_freq,
					  ad7768_clk_config[idx].clk_div);

	return 0;
}