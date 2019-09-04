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
struct kmx61_data {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_MAGN ; 
 struct kmx61_data* kmx61_get_data (struct iio_dev*) ; 
 int kmx61_set_odr (struct kmx61_data*,int,int,int /*<<< orphan*/ ) ; 
 int kmx61_set_scale (struct kmx61_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kmx61_write_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan, int val,
			   int val2, long mask)
{
	int ret;
	struct kmx61_data *data = kmx61_get_data(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (chan->type != IIO_ACCEL && chan->type != IIO_MAGN)
			return -EINVAL;

		mutex_lock(&data->lock);
		ret = kmx61_set_odr(data, val, val2, chan->address);
		mutex_unlock(&data->lock);
		return ret;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ACCEL:
			if (val != 0)
				return -EINVAL;
			mutex_lock(&data->lock);
			ret = kmx61_set_scale(data, val2);
			mutex_unlock(&data->lock);
			return ret;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}