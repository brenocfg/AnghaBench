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
struct stk8312_data {int mode; size_t sample_rate_idx; int /*<<< orphan*/  range; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int val; int val2; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int STK8312_MODE_ACTIVE ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct stk8312_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 
 int stk8312_read_accel (struct stk8312_data*,int /*<<< orphan*/ ) ; 
 TYPE_1__* stk8312_samp_freq_table ; 
 int** stk8312_scale_table ; 
 int stk8312_set_mode (struct stk8312_data*,int) ; 

__attribute__((used)) static int stk8312_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct stk8312_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (iio_buffer_enabled(indio_dev))
			return -EBUSY;
		mutex_lock(&data->lock);
		ret = stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
		if (ret < 0) {
			mutex_unlock(&data->lock);
			return ret;
		}
		ret = stk8312_read_accel(data, chan->address);
		if (ret < 0) {
			stk8312_set_mode(data,
					 data->mode & (~STK8312_MODE_ACTIVE));
			mutex_unlock(&data->lock);
			return ret;
		}
		*val = sign_extend32(ret, 7);
		ret = stk8312_set_mode(data,
				       data->mode & (~STK8312_MODE_ACTIVE));
		mutex_unlock(&data->lock);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = stk8312_scale_table[data->range - 1][0];
		*val2 = stk8312_scale_table[data->range - 1][1];
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = stk8312_samp_freq_table[data->sample_rate_idx].val;
		*val2 = stk8312_samp_freq_table[data->sample_rate_idx].val2;
		return IIO_VAL_INT_PLUS_MICRO;
	}

	return -EINVAL;
}