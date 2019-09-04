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
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct ads1015_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int ads1015_set_data_rate (struct ads1015_data*,int /*<<< orphan*/ ,int) ; 
 int ads1015_set_scale (struct ads1015_data*,struct iio_chan_spec const*,int,int) ; 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads1015_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan, int val,
			     int val2, long mask)
{
	struct ads1015_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->lock);
	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		ret = ads1015_set_scale(data, chan, val, val2);
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = ads1015_set_data_rate(data, chan->address, val);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	mutex_unlock(&data->lock);

	return ret;
}