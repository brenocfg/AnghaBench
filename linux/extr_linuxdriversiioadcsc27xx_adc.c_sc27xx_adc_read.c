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
typedef  int u32 ;
struct sc27xx_adc_data {int value; int /*<<< orphan*/  hwlock; scalar_t__ base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  completion; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SC27XX_ADC_12BIT_MODE ; 
 int SC27XX_ADC_CHN_ID_MASK ; 
 int SC27XX_ADC_CHN_RUN ; 
 scalar_t__ SC27XX_ADC_CH_CFG ; 
 scalar_t__ SC27XX_ADC_CTL ; 
 int SC27XX_ADC_EN ; 
 int /*<<< orphan*/  SC27XX_ADC_HWLOCK_TIMEOUT ; 
 int SC27XX_ADC_RUN_NUM_MASK ; 
 int SC27XX_ADC_RUN_NUM_SHIFT ; 
 int SC27XX_ADC_SCALE_MASK ; 
 int SC27XX_ADC_SCALE_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hwspin_lock_timeout_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwspin_unlock_raw (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sc27xx_adc_read(struct sc27xx_adc_data *data, int channel,
			   int scale, int *val)
{
	int ret;
	u32 tmp;

	reinit_completion(&data->completion);

	ret = hwspin_lock_timeout_raw(data->hwlock, SC27XX_ADC_HWLOCK_TIMEOUT);
	if (ret) {
		dev_err(data->dev, "timeout to get the hwspinlock\n");
		return ret;
	}

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
				 SC27XX_ADC_EN, SC27XX_ADC_EN);
	if (ret)
		goto unlock_adc;

	/* Configure the channel id and scale */
	tmp = (scale << SC27XX_ADC_SCALE_SHIFT) & SC27XX_ADC_SCALE_MASK;
	tmp |= channel & SC27XX_ADC_CHN_ID_MASK;
	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CH_CFG,
				 SC27XX_ADC_CHN_ID_MASK | SC27XX_ADC_SCALE_MASK,
				 tmp);
	if (ret)
		goto disable_adc;

	/* Select 12bit conversion mode, and only sample 1 time */
	tmp = SC27XX_ADC_12BIT_MODE;
	tmp |= (0 << SC27XX_ADC_RUN_NUM_SHIFT) & SC27XX_ADC_RUN_NUM_MASK;
	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
				 SC27XX_ADC_RUN_NUM_MASK | SC27XX_ADC_12BIT_MODE,
				 tmp);
	if (ret)
		goto disable_adc;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
				 SC27XX_ADC_CHN_RUN, SC27XX_ADC_CHN_RUN);
	if (ret)
		goto disable_adc;

	wait_for_completion(&data->completion);

disable_adc:
	regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
			   SC27XX_ADC_EN, 0);
unlock_adc:
	hwspin_unlock_raw(data->hwlock);

	if (!ret)
		*val = data->value;

	return ret;
}