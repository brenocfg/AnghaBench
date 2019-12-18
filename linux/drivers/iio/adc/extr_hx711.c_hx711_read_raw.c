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
struct hx711_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  gain_set; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int hx711_get_gain_to_scale (int /*<<< orphan*/ ) ; 
 int hx711_reset_read (struct hx711_data*,int /*<<< orphan*/ ) ; 
 struct hx711_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hx711_read_raw(struct iio_dev *indio_dev,
				const struct iio_chan_spec *chan,
				int *val, int *val2, long mask)
{
	struct hx711_data *hx711_data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&hx711_data->lock);

		*val = hx711_reset_read(hx711_data, chan->channel);

		mutex_unlock(&hx711_data->lock);

		if (*val < 0)
			return *val;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		mutex_lock(&hx711_data->lock);

		*val2 = hx711_get_gain_to_scale(hx711_data->gain_set);

		mutex_unlock(&hx711_data->lock);

		return IIO_VAL_INT_PLUS_NANO;
	default:
		return -EINVAL;
	}
}