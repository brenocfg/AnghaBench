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
struct us5182d_data {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 128 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int us5182d_apply_scale (struct us5182d_data*,int) ; 
 int* us5182d_scales ; 

__attribute__((used)) static int us5182d_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan, int val,
			     int val2, long mask)
{
	struct us5182d_data *data = iio_priv(indio_dev);
	int ret, i;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		if (val != 0)
			return -EINVAL;
		for (i = 0; i < ARRAY_SIZE(us5182d_scales); i++)
			if (val2 == us5182d_scales[i]) {
				mutex_lock(&data->lock);
				ret = us5182d_apply_scale(data, i);
				mutex_unlock(&data->lock);
				return ret;
			}
		break;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}