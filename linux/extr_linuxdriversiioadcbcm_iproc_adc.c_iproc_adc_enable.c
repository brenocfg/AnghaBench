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
struct iproc_adc_priv {int chan_val; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IPROC_ADC_CHANNEL_INTERRUPT_MASK ; 
 scalar_t__ IPROC_ADC_CHANNEL_INTERRUPT_STATUS ; 
 int IPROC_ADC_CHANNEL_OFFSET ; 
 int /*<<< orphan*/  IPROC_ADC_CHANNEL_SEL_MASK ; 
 int IPROC_ADC_CONTROLLER_EN ; 
 int IPROC_ADC_PWR_ADC ; 
 int IPROC_ADC_PWR_BG ; 
 int IPROC_ADC_PWR_LDO ; 
 int /*<<< orphan*/  IPROC_ANALOG_CONTROL ; 
 scalar_t__ IPROC_REGCTL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct iproc_adc_priv* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int iproc_adc_enable(struct iio_dev *indio_dev)
{
	u32 val;
	u32 channel_id;
	struct iproc_adc_priv *adc_priv = iio_priv(indio_dev);
	int ret;

	/* Set i_amux = 3b'000, select channel 0 */
	ret = regmap_update_bits(adc_priv->regmap, IPROC_ANALOG_CONTROL,
				IPROC_ADC_CHANNEL_SEL_MASK, 0);
	if (ret) {
		dev_err(&indio_dev->dev,
			"failed to write IPROC_ANALOG_CONTROL %d\n", ret);
		return ret;
	}
	adc_priv->chan_val = -1;

	/*
	 * PWR up LDO, ADC, and Band Gap (0 to enable)
	 * Also enable ADC controller (set high)
	 */
	ret = regmap_read(adc_priv->regmap, IPROC_REGCTL2, &val);
	if (ret) {
		dev_err(&indio_dev->dev,
			"failed to read IPROC_REGCTL2 %d\n", ret);
		return ret;
	}

	val &= ~(IPROC_ADC_PWR_LDO | IPROC_ADC_PWR_ADC | IPROC_ADC_PWR_BG);

	ret = regmap_write(adc_priv->regmap, IPROC_REGCTL2, val);
	if (ret) {
		dev_err(&indio_dev->dev,
			"failed to write IPROC_REGCTL2 %d\n", ret);
		return ret;
	}

	ret = regmap_read(adc_priv->regmap, IPROC_REGCTL2, &val);
	if (ret) {
		dev_err(&indio_dev->dev,
			"failed to read IPROC_REGCTL2 %d\n", ret);
		return ret;
	}

	val |= IPROC_ADC_CONTROLLER_EN;
	ret = regmap_write(adc_priv->regmap, IPROC_REGCTL2, val);
	if (ret) {
		dev_err(&indio_dev->dev,
			"failed to write IPROC_REGCTL2 %d\n", ret);
		return ret;
	}

	for (channel_id = 0; channel_id < indio_dev->num_channels;
		channel_id++) {
		ret = regmap_write(adc_priv->regmap,
				IPROC_ADC_CHANNEL_INTERRUPT_MASK +
				IPROC_ADC_CHANNEL_OFFSET * channel_id, 0);
		if (ret) {
			dev_err(&indio_dev->dev,
			    "failed to write ADC_CHANNEL_INTERRUPT_MASK %d\n",
			    ret);
			return ret;
		}

		ret = regmap_write(adc_priv->regmap,
				IPROC_ADC_CHANNEL_INTERRUPT_STATUS +
				IPROC_ADC_CHANNEL_OFFSET * channel_id, 0);
		if (ret) {
			dev_err(&indio_dev->dev,
			    "failed to write ADC_CHANNEL_INTERRUPT_STATUS %d\n",
			    ret);
			return ret;
		}
	}

	return 0;
}