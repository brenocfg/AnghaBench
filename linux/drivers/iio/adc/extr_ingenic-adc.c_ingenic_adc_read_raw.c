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
struct ingenic_adc {TYPE_1__* soc_data; int /*<<< orphan*/  low_vref_mode; int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int battery_high_vref; int battery_high_vref_bits; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
#define  INGENIC_ADC_AUX 129 
#define  INGENIC_ADC_BATTERY 128 
 int JZ_ADC_AUX_VREF ; 
 int JZ_ADC_AUX_VREF_BITS ; 
 int JZ_ADC_BATTERY_LOW_VREF ; 
 int JZ_ADC_BATTERY_LOW_VREF_BITS ; 
 scalar_t__ JZ_ADC_REG_ADBDAT ; 
 scalar_t__ JZ_ADC_REG_ADSDAT ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct ingenic_adc* iio_priv (struct iio_dev*) ; 
 int ingenic_adc_capture (struct ingenic_adc*,int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static int ingenic_adc_read_raw(struct iio_dev *iio_dev,
				struct iio_chan_spec const *chan,
				int *val,
				int *val2,
				long m)
{
	struct ingenic_adc *adc = iio_priv(iio_dev);
	int ret;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		clk_enable(adc->clk);
		ret = ingenic_adc_capture(adc, chan->channel);
		if (ret) {
			clk_disable(adc->clk);
			return ret;
		}

		switch (chan->channel) {
		case INGENIC_ADC_AUX:
			*val = readw(adc->base + JZ_ADC_REG_ADSDAT);
			break;
		case INGENIC_ADC_BATTERY:
			*val = readw(adc->base + JZ_ADC_REG_ADBDAT);
			break;
		}

		clk_disable(adc->clk);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->channel) {
		case INGENIC_ADC_AUX:
			*val = JZ_ADC_AUX_VREF;
			*val2 = JZ_ADC_AUX_VREF_BITS;
			break;
		case INGENIC_ADC_BATTERY:
			if (adc->low_vref_mode) {
				*val = JZ_ADC_BATTERY_LOW_VREF;
				*val2 = JZ_ADC_BATTERY_LOW_VREF_BITS;
			} else {
				*val = adc->soc_data->battery_high_vref;
				*val2 = adc->soc_data->battery_high_vref_bits;
			}
			break;
		}

		return IIO_VAL_FRACTIONAL_LOG2;
	default:
		return -EINVAL;
	}
}