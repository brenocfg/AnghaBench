#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;
struct dac5571_data {int* val; int (* dac5571_cmd ) (struct dac5571_data*,size_t,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  powerdown; TYPE_1__* spec; } ;
struct TYPE_2__ {int resolution; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 struct dac5571_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dac5571_data*,size_t,int) ; 

__attribute__((used)) static int dac5571_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct dac5571_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (data->val[chan->channel] == val)
			return 0;

		if (val >= (1 << data->spec->resolution) || val < 0)
			return -EINVAL;

		if (data->powerdown)
			return -EBUSY;

		mutex_lock(&data->lock);
		ret = data->dac5571_cmd(data, chan->channel, val);
		if (ret == 0)
			data->val[chan->channel] = val;
		mutex_unlock(&data->lock);
		return ret;

	default:
		return -EINVAL;
	}
}