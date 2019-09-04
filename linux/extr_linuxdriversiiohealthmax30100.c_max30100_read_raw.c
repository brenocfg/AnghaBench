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
struct max30100_data {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct max30100_data* iio_priv (struct iio_dev*) ; 
 int max30100_get_temp (struct max30100_data*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max30100_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct max30100_data *data = iio_priv(indio_dev);
	int ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		/*
		 * Temperature reading can only be acquired while engine
		 * is running
		 */
		mutex_lock(&indio_dev->mlock);

		if (!iio_buffer_enabled(indio_dev))
			ret = -EAGAIN;
		else {
			ret = max30100_get_temp(data, val);
			if (!ret)
				ret = IIO_VAL_INT;

		}

		mutex_unlock(&indio_dev->mlock);
		break;
	case IIO_CHAN_INFO_SCALE:
		*val = 1;  /* 0.0625 */
		*val2 = 16;
		ret = IIO_VAL_FRACTIONAL;
		break;
	}

	return ret;
}