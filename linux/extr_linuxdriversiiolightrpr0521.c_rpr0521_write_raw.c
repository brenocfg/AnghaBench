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
struct rpr0521_data {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 struct rpr0521_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpr0521_set_gain (struct rpr0521_data*,int /*<<< orphan*/ ,int,int) ; 
 int rpr0521_write_ps_offset (struct rpr0521_data*,int) ; 
 int rpr0521_write_samp_freq_common (struct rpr0521_data*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rpr0521_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan, int val,
			     int val2, long mask)
{
	struct rpr0521_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		mutex_lock(&data->lock);
		ret = rpr0521_set_gain(data, chan->address, val, val2);
		mutex_unlock(&data->lock);

		return ret;

	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->lock);
		ret = rpr0521_write_samp_freq_common(data, chan->type,
						     val, val2);
		mutex_unlock(&data->lock);

		return ret;

	case IIO_CHAN_INFO_OFFSET:
		mutex_lock(&data->lock);
		ret = rpr0521_write_ps_offset(data, val);
		mutex_unlock(&data->lock);

		return ret;

	default:
		return -EINVAL;
	}
}