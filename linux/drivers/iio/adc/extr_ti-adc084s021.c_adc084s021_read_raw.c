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
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int shift; } ;
struct iio_chan_spec {int channel; TYPE_1__ scan_type; } ;
struct adc084s021 {int* tx_buf; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int adc084s021_adc_conversion (struct adc084s021*,int*) ; 
 int be16_to_cpu (int) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct adc084s021* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc084s021_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *channel, int *val,
			   int *val2, long mask)
{
	struct adc084s021 *adc = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret < 0)
			return ret;

		ret = regulator_enable(adc->reg);
		if (ret) {
			iio_device_release_direct_mode(indio_dev);
			return ret;
		}

		adc->tx_buf[0] = channel->channel << 3;
		ret = adc084s021_adc_conversion(adc, val);
		iio_device_release_direct_mode(indio_dev);
		regulator_disable(adc->reg);
		if (ret < 0)
			return ret;

		*val = be16_to_cpu(*val);
		*val = (*val >> channel->scan_type.shift) & 0xff;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ret = regulator_enable(adc->reg);
		if (ret)
			return ret;

		ret = regulator_get_voltage(adc->reg);
		regulator_disable(adc->reg);
		if (ret < 0)
			return ret;

		*val = ret / 1000;

		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}