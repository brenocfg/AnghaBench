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
struct TYPE_2__ {int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;
struct adc108s102_state {int va_millivolt; } ;

/* Variables and functions */
 int ADC108S102_RES_DATA (int) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int adc108s102_scan_direct (struct adc108s102_state*,int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct adc108s102_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adc108s102_read_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int *val, int *val2, long m)
{
	struct adc108s102_state *st = iio_priv(indio_dev);
	int ret;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;

		ret = adc108s102_scan_direct(st, chan->address);

		iio_device_release_direct_mode(indio_dev);

		if (ret < 0)
			return ret;

		*val = ADC108S102_RES_DATA(ret);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type != IIO_VOLTAGE)
			break;

		*val = st->va_millivolt;
		*val2 = chan->scan_type.realbits;

		return IIO_VAL_FRACTIONAL_LOG2;
	default:
		break;
	}

	return -EINVAL;
}