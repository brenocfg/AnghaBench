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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  differential; int /*<<< orphan*/  channel; } ;
struct adc0832 {int /*<<< orphan*/  reg; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int adc0832_adc_conversion (struct adc0832*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adc0832* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc0832_read_raw(struct iio_dev *iio,
			struct iio_chan_spec const *channel, int *value,
			int *shift, long mask)
{
	struct adc0832 *adc = iio_priv(iio);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		*value = adc0832_adc_conversion(adc, channel->channel,
						channel->differential);
		mutex_unlock(&adc->lock);
		if (*value < 0)
			return *value;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*value = regulator_get_voltage(adc->reg);
		if (*value < 0)
			return *value;

		/* convert regulator output voltage to mV */
		*value /= 1000;
		*shift = 8;

		return IIO_VAL_FRACTIONAL_LOG2;
	}

	return -EINVAL;
}