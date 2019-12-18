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
struct max1118 {int /*<<< orphan*/  spi; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 struct max1118* iio_priv (struct iio_dev*) ; 
 int max1118_get_vref_mV (int /*<<< orphan*/ ) ; 
 int max1118_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max1118_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int *val, int *val2, long mask)
{
	struct max1118 *adc = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		*val = max1118_read(adc->spi, chan->channel);
		mutex_unlock(&adc->lock);
		if (*val < 0)
			return *val;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = max1118_get_vref_mV(adc->spi);
		if (*val < 0)
			return *val;
		*val2 = 8;

		return IIO_VAL_FRACTIONAL_LOG2;
	}

	return -EINVAL;
}