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
struct ingenic_adc {int low_vref_mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 129 
#define  INGENIC_ADC_BATTERY 128 
 int JZ_ADC_BATTERY_LOW_VREF ; 
 int /*<<< orphan*/  JZ_ADC_REG_CFG_BAT_MD ; 
 struct ingenic_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ingenic_adc_set_config (struct ingenic_adc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ingenic_adc_write_raw(struct iio_dev *iio_dev,
				 struct iio_chan_spec const *chan,
				 int val,
				 int val2,
				 long m)
{
	struct ingenic_adc *adc = iio_priv(iio_dev);

	switch (m) {
	case IIO_CHAN_INFO_SCALE:
		switch (chan->channel) {
		case INGENIC_ADC_BATTERY:
			if (val > JZ_ADC_BATTERY_LOW_VREF) {
				ingenic_adc_set_config(adc,
						       JZ_ADC_REG_CFG_BAT_MD,
						       0);
				adc->low_vref_mode = false;
			} else {
				ingenic_adc_set_config(adc,
						       JZ_ADC_REG_CFG_BAT_MD,
						       JZ_ADC_REG_CFG_BAT_MD);
				adc->low_vref_mode = true;
			}
			return 0;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}