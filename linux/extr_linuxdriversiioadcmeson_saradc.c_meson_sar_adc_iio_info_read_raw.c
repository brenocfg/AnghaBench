#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct meson_sar_adc_priv {int calibbias; int calibscale; TYPE_3__* data; int /*<<< orphan*/  vref; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_6__ {TYPE_2__* param; } ;
struct TYPE_5__ {int resolution; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIGHT_SAMPLES ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_AVERAGE_RAW 132 
#define  IIO_CHAN_INFO_CALIBBIAS 131 
#define  IIO_CHAN_INFO_CALIBSCALE 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  MEAN_AVERAGING ; 
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
		ret = regulator_get_voltage(priv->vref);
		if (ret < 0) {
			dev_err(indio_dev->dev.parent,
				"failed to get vref voltage: %d\n", ret);
			return ret;
		}

		*val = ret / 1000;
		*val2 = priv->data->param->resolution;
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_CALIBBIAS:
		*val = priv->calibbias;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_CALIBSCALE:
		*val = priv->calibscale / MILLION;
		*val2 = priv->calibscale % MILLION;
		return IIO_VAL_INT_PLUS_MICRO;

	default:
		return -EINVAL;
	}
}