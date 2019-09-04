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
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct dln2_adc {int sample_period; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int dln2_adc_read (struct dln2_adc*,int /*<<< orphan*/ ) ; 
 struct dln2_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dln2_adc_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val,
			     int *val2,
			     long mask)
{
	int ret;
	unsigned int microhertz;
	struct dln2_adc *dln2 = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&dln2->mutex);
		ret = dln2_adc_read(dln2, chan->channel);
		mutex_unlock(&dln2->mutex);

		if (ret < 0)
			return ret;

		*val = ret;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		/*
		 * Voltage reference is fixed at 3.3v
		 *  3.3 / (1 << 10) * 1000000000
		 */
		*val = 0;
		*val2 = 3222656;
		return IIO_VAL_INT_PLUS_NANO;

	case IIO_CHAN_INFO_SAMP_FREQ:
		if (dln2->sample_period) {
			microhertz = 1000000000 / dln2->sample_period;
			*val = microhertz / 1000000;
			*val2 = microhertz % 1000000;
		} else {
			*val = 0;
			*val2 = 0;
		}

		return IIO_VAL_INT_PLUS_MICRO;

	default:
		return -EINVAL;
	}
}