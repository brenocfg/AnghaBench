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
struct sc27xx_adc_data {int /*<<< orphan*/  hwlock; scalar_t__ base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SC27XX_ADC_12BIT_MODE ; 
 int SC27XX_ADC_CHN_ID_MASK ; 
 int SC27XX_ADC_CHN_RUN ; 
 scalar_t__ SC27XX_ADC_CH_CFG ; 
 scalar_t__ SC27XX_ADC_CTL ; 
 scalar_t__ SC27XX_ADC_DATA ; 
 int SC27XX_ADC_DATA_MASK ; 
 int SC27XX_ADC_EN ; 
 int /*<<< orphan*/  SC27XX_ADC_HWLOCK_TIMEOUT ; 
 scalar_t__ SC27XX_ADC_INT_CLR ; 
 scalar_t__ SC27XX_ADC_INT_RAW ; 
 int SC27XX_ADC_IRQ_CLR ; 
 int SC27XX_ADC_IRQ_RAW ; 
 int /*<<< orphan*/  SC27XX_ADC_POLL_RAW_STATUS ; 
 int /*<<< orphan*/  SC27XX_ADC_RDY_TIMEOUT ; 
 int SC27XX_ADC_RUN_NUM_MASK ; 
 int SC27XX_ADC_RUN_NUM_SHIFT ; 
 int SC27XX_ADC_SCALE_MASK ; 
 int SC27XX_ADC_SCALE_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hwspin_lock_timeout_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwspin_unlock_raw (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int sc27xx_adc_read(struct sc27xx_adc_data *data, int channel,
			   int scale, int *val)
{
	int ret;
	u32 tmp, value, status;

	ret = hwspin_lock_timeout_raw(data->hwlock, SC27XX_ADC_HWLOCK_TIMEOUT);
	if (ret) {
		dev_err(data->dev, "timeout to get the hwspinlock\n");
		return ret;
	}

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
				 SC27XX_ADC_EN, SC27XX_ADC_EN);
	if (ret)
		goto unlock_adc;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_INT_CLR,
				 SC27XX_ADC_IRQ_CLR, SC27XX_ADC_IRQ_CLR);
	if (ret)
		goto disable_adc;

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

	ret = regmap_read_poll_timeout(data->regmap,
				       data->base + SC27XX_ADC_INT_RAW,
				       status, (status & SC27XX_ADC_IRQ_RAW),
				       SC27XX_ADC_POLL_RAW_STATUS,
				       SC27XX_ADC_RDY_TIMEOUT);
	if (ret) {
		dev_err(data->dev, "read adc timeout, status = 0x%x\n", status);
		goto disable_adc;
	}

	ret = regmap_read(data->regmap, data->base + SC27XX_ADC_DATA, &value);
	if (ret)
		goto disable_adc;

	value &= SC27XX_ADC_DATA_MASK;

disable_adc:
	regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
			   SC27XX_ADC_EN, 0);
unlock_adc:
	hwspin_unlock_raw(data->hwlock);

	if (!ret)
		*val = value;

	return ret;
}