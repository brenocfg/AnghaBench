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
struct TYPE_2__ {int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;
struct adc12138 {int /*<<< orphan*/  vref_n; int /*<<< orphan*/  vref_p; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int adc12138_adc_conversion (struct adc12138*,struct iio_chan_spec const*,int /*<<< orphan*/ *) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct adc12138* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int adc12138_read_raw(struct iio_dev *iio,
			     struct iio_chan_spec const *channel, int *value,
			     int *shift, long mask)
{
	struct adc12138 *adc = iio_priv(iio);
	int ret;
	__be16 data;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		ret = adc12138_adc_conversion(adc, channel, &data);
		mutex_unlock(&adc->lock);
		if (ret)
			return ret;

		*value = sign_extend32(be16_to_cpu(data) >> 3, 12);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(adc->vref_p);
		if (ret < 0)
			return ret;
		*value = ret;

		if (!IS_ERR(adc->vref_n)) {
			ret = regulator_get_voltage(adc->vref_n);
			if (ret < 0)
				return ret;
			*value -= ret;
		}

		/* convert regulator output voltage to mV */
		*value /= 1000;
		*shift = channel->scan_type.realbits - 1;

		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_OFFSET:
		if (!IS_ERR(adc->vref_n)) {
			*value = regulator_get_voltage(adc->vref_n);
			if (*value < 0)
				return *value;
		} else {
			*value = 0;
		}

		/* convert regulator output voltage to mV */
		*value /= 1000;

		return IIO_VAL_INT;
	}

	return -EINVAL;
}