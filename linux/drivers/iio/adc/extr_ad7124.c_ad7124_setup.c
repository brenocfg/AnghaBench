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
struct ad7124_state {unsigned int adc_control; int num_channels; int /*<<< orphan*/  sd; TYPE_1__* channel_config; int /*<<< orphan*/  mclk; } ;
struct TYPE_2__ {unsigned int ain; int buf_positive; int buf_negative; int /*<<< orphan*/  refsel; int /*<<< orphan*/  bipolar; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7124_ADC_CONTROL ; 
 unsigned int AD7124_ADC_CTRL_PWR (unsigned int) ; 
 unsigned int AD7124_ADC_CTRL_PWR_MSK ; 
 int /*<<< orphan*/  AD7124_CHANNEL (int) ; 
 unsigned int AD7124_CHANNEL_SETUP (int) ; 
 int /*<<< orphan*/  AD7124_CONFIG (int) ; 
 unsigned int AD7124_CONFIG_BIPOLAR (int /*<<< orphan*/ ) ; 
 unsigned int AD7124_CONFIG_IN_BUFF (int) ; 
 unsigned int AD7124_CONFIG_REF_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 unsigned int ad7124_find_closest_match (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 int ad7124_init_channel_vref (struct ad7124_state*,int) ; 
 unsigned int* ad7124_master_clk_freq_hz ; 
 int ad7124_set_channel_odr (struct ad7124_state*,int,int) ; 
 int ad_sd_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ad7124_setup(struct ad7124_state *st)
{
	unsigned int val, fclk, power_mode;
	int i, ret, tmp;

	fclk = clk_get_rate(st->mclk);
	if (!fclk)
		return -EINVAL;

	/* The power mode changes the master clock frequency */
	power_mode = ad7124_find_closest_match(ad7124_master_clk_freq_hz,
					ARRAY_SIZE(ad7124_master_clk_freq_hz),
					fclk);
	if (fclk != ad7124_master_clk_freq_hz[power_mode]) {
		ret = clk_set_rate(st->mclk, fclk);
		if (ret)
			return ret;
	}

	/* Set the power mode */
	st->adc_control &= ~AD7124_ADC_CTRL_PWR_MSK;
	st->adc_control |= AD7124_ADC_CTRL_PWR(power_mode);
	ret = ad_sd_write_reg(&st->sd, AD7124_ADC_CONTROL, 2, st->adc_control);
	if (ret < 0)
		return ret;

	for (i = 0; i < st->num_channels; i++) {
		val = st->channel_config[i].ain | AD7124_CHANNEL_SETUP(i);
		ret = ad_sd_write_reg(&st->sd, AD7124_CHANNEL(i), 2, val);
		if (ret < 0)
			return ret;

		ret = ad7124_init_channel_vref(st, i);
		if (ret < 0)
			return ret;

		tmp = (st->channel_config[i].buf_positive << 1)  +
			st->channel_config[i].buf_negative;

		val = AD7124_CONFIG_BIPOLAR(st->channel_config[i].bipolar) |
		      AD7124_CONFIG_REF_SEL(st->channel_config[i].refsel) |
		      AD7124_CONFIG_IN_BUFF(tmp);
		ret = ad_sd_write_reg(&st->sd, AD7124_CONFIG(i), 2, val);
		if (ret < 0)
			return ret;
		/*
		 * 9.38 SPS is the minimum output data rate supported
		 * regardless of the selected power mode. Round it up to 10 and
		 * set all the enabled channels to this default value.
		 */
		ret = ad7124_set_channel_odr(st, i, 10);
	}

	return ret;
}