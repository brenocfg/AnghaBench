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
struct ti_adc_data {int /*<<< orphan*/  ref; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;

/* Variables and functions */
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ti_adc_data* iio_priv (struct iio_dev*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int ti_adc_read_measurement (struct ti_adc_data*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int ti_adc_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct ti_adc_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;

		ret = ti_adc_read_measurement(data, chan, val);
		iio_device_release_direct_mode(indio_dev);

		if (ret)
			return ret;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(data->ref);
		if (ret < 0)
			return ret;

		*val = ret / 1000;
		*val2 = chan->scan_type.realbits;

		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_OFFSET:
		*val = 1 << (chan->scan_type.realbits - 1);
		return IIO_VAL_INT;
	}

	return 0;
}