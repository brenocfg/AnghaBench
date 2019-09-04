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
struct mxs_lradc_adc {int* vref_mv; int /*<<< orphan*/  is_divided; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int realbits; } ;
struct iio_chan_spec {size_t channel; int /*<<< orphan*/  type; TYPE_1__ scan_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_TEMP ; 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 int mxs_lradc_adc_read_single (struct iio_dev*,size_t,int*) ; 
 int mxs_lradc_adc_read_temp (struct iio_dev*,int*) ; 
 int test_bit (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxs_lradc_adc_read_raw(struct iio_dev *iio_dev,
			      const struct iio_chan_spec *chan,
			      int *val, int *val2, long m)
{
	struct mxs_lradc_adc *adc = iio_priv(iio_dev);

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type == IIO_TEMP)
			return mxs_lradc_adc_read_temp(iio_dev, val);

		return mxs_lradc_adc_read_single(iio_dev, chan->channel, val);

	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_TEMP) {
			/*
			 * From the datasheet, we have to multiply by 1.012 and
			 * divide by 4
			 */
			*val = 0;
			*val2 = 253000;
			return IIO_VAL_INT_PLUS_MICRO;
		}

		*val = adc->vref_mv[chan->channel];
		*val2 = chan->scan_type.realbits -
			test_bit(chan->channel, &adc->is_divided);
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_OFFSET:
		if (chan->type == IIO_TEMP) {
			/*
			 * The calculated value from the ADC is in Kelvin, we
			 * want Celsius for hwmon so the offset is -273.15
			 * The offset is applied before scaling so it is
			 * actually -213.15 * 4 / 1.012 = -1079.644268
			 */
			*val = -1079;
			*val2 = 644268;

			return IIO_VAL_INT_PLUS_MICRO;
		}

		return -EINVAL;

	default:
		break;
	}

	return -EINVAL;
}