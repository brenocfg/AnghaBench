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
struct ms_ht_dev {int res_index; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int* htu21_samp_freq ; 
 struct ms_ht_dev* iio_priv (struct iio_dev*) ; 
 int ms_sensors_write_resolution (struct ms_ht_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int htu21_write_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int val, int val2, long mask)
{
	struct ms_ht_dev *dev_data = iio_priv(indio_dev);
	int i, ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		i = ARRAY_SIZE(htu21_samp_freq);
		while (i-- > 0)
			if (val == htu21_samp_freq[i])
				break;
		if (i < 0)
			return -EINVAL;
		mutex_lock(&dev_data->lock);
		dev_data->res_index = i;
		ret = ms_sensors_write_resolution(dev_data, i);
		mutex_unlock(&dev_data->lock);

		return ret;
	default:
		return -EINVAL;
	}
}