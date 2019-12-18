#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct meson_sar_adc_priv {int calibbias; int calibscale; int temperature_sensor_adc_val; TYPE_2__* param; int /*<<< orphan*/  vref; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int resolution; int temperature_multiplier; int temperature_divider; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  EIGHT_SAMPLES ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_AVERAGE_RAW 133 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_CALIBSCALE 131 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_TEMP ; 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int /*<<< orphan*/  MEAN_AVERAGING ; 
 int MESON_SAR_ADC_TEMP_OFFSET ; 
 int MILLION ; 
 int /*<<< orphan*/  NO_AVERAGING ; 
 int /*<<< orphan*/  ONE_SAMPLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int meson_sar_adc_get_sample (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_sar_adc_iio_info_read_raw(struct iio_dev *indio_dev,
					   const struct iio_chan_spec *chan,
					   int *val, int *val2, long mask)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return meson_sar_adc_get_sample(indio_dev, chan, NO_AVERAGING,
						ONE_SAMPLE, val);
		break;

	case IIO_CHAN_INFO_AVERAGE_RAW:
		return meson_sar_adc_get_sample(indio_dev, chan,
						MEAN_AVERAGING, EIGHT_SAMPLES,
						val);
		break;

	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_VOLTAGE) {
			ret = regulator_get_voltage(priv->vref);
			if (ret < 0) {
				dev_err(indio_dev->dev.parent,
					"failed to get vref voltage: %d\n",
					ret);
				return ret;
			}

			*val = ret / 1000;
			*val2 = priv->param->resolution;
			return IIO_VAL_FRACTIONAL_LOG2;
		} else if (chan->type == IIO_TEMP) {
			/* SoC specific multiplier and divider */
			*val = priv->param->temperature_multiplier;
			*val2 = priv->param->temperature_divider;

			/* celsius to millicelsius */
			*val *= 1000;

			return IIO_VAL_FRACTIONAL;
		} else {
			return -EINVAL;
		}

	case IIO_CHAN_INFO_CALIBBIAS:
		*val = priv->calibbias;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_CALIBSCALE:
		*val = priv->calibscale / MILLION;
		*val2 = priv->calibscale % MILLION;
		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_CHAN_INFO_OFFSET:
		*val = DIV_ROUND_CLOSEST(MESON_SAR_ADC_TEMP_OFFSET *
					 priv->param->temperature_divider,
					 priv->param->temperature_multiplier);
		*val -= priv->temperature_sensor_adc_val;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}