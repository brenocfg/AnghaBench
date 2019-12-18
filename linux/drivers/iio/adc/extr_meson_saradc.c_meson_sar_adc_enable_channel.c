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
typedef  scalar_t__ u32 ;
struct meson_sar_adc_priv {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ address; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ FIELD_PREP (scalar_t__,scalar_t__) ; 
 scalar_t__ IIO_TEMP ; 
 int /*<<< orphan*/  MESON_SAR_ADC_CHAN_LIST ; 
 scalar_t__ MESON_SAR_ADC_CHAN_LIST_ENTRY_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ MESON_SAR_ADC_CHAN_LIST_MAX_INDEX_MASK ; 
 int /*<<< orphan*/  MESON_SAR_ADC_DELTA_10 ; 
 scalar_t__ MESON_SAR_ADC_DELTA_10_TEMP_SEL ; 
 int /*<<< orphan*/  MESON_SAR_ADC_DETECT_IDLE_SW ; 
 scalar_t__ MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_MUX_MASK ; 
 scalar_t__ MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_MUX_SEL_MASK ; 
 scalar_t__ MESON_SAR_ADC_VOLTAGE_AND_TEMP_CHANNEL ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void meson_sar_adc_enable_channel(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	u32 regval;

	/*
	 * the SAR ADC engine allows sampling multiple channels at the same
	 * time. to keep it simple we're only working with one *internal*
	 * channel, which starts counting at index 0 (which means: count = 1).
	 */
	regval = FIELD_PREP(MESON_SAR_ADC_CHAN_LIST_MAX_INDEX_MASK, 0);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_CHAN_LIST,
			   MESON_SAR_ADC_CHAN_LIST_MAX_INDEX_MASK, regval);

	/* map channel index 0 to the channel which we want to read */
	regval = FIELD_PREP(MESON_SAR_ADC_CHAN_LIST_ENTRY_MASK(0),
			    chan->address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_CHAN_LIST,
			   MESON_SAR_ADC_CHAN_LIST_ENTRY_MASK(0), regval);

	regval = FIELD_PREP(MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_MUX_MASK,
			    chan->address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DETECT_IDLE_SW,
			   MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_MUX_MASK,
			   regval);

	regval = FIELD_PREP(MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_MUX_SEL_MASK,
			    chan->address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DETECT_IDLE_SW,
			   MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_MUX_SEL_MASK,
			   regval);

	if (chan->address == MESON_SAR_ADC_VOLTAGE_AND_TEMP_CHANNEL) {
		if (chan->type == IIO_TEMP)
			regval = MESON_SAR_ADC_DELTA_10_TEMP_SEL;
		else
			regval = 0;

		regmap_update_bits(priv->regmap,
				   MESON_SAR_ADC_DELTA_10,
				   MESON_SAR_ADC_DELTA_10_TEMP_SEL, regval);
	}
}