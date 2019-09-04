#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stk8ba50_data {size_t range; size_t sample_rate_idx; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct TYPE_4__ {int samp_freq; } ;
struct TYPE_3__ {int scale_val; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int STK8BA50_DATA_SHIFT ; 
 int /*<<< orphan*/  STK8BA50_MODE_NORMAL ; 
 int /*<<< orphan*/  STK8BA50_MODE_SUSPEND ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct stk8ba50_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 
 int stk8ba50_read_accel (struct stk8ba50_data*,int /*<<< orphan*/ ) ; 
 TYPE_2__* stk8ba50_samp_freq_table ; 
 TYPE_1__* stk8ba50_scale_table ; 
 int stk8ba50_set_power (struct stk8ba50_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stk8ba50_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct stk8ba50_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (iio_buffer_enabled(indio_dev))
			return -EBUSY;
		mutex_lock(&data->lock);
		ret = stk8ba50_set_power(data, STK8BA50_MODE_NORMAL);
		if (ret < 0) {
			mutex_unlock(&data->lock);
			return -EINVAL;
		}
		ret = stk8ba50_read_accel(data, chan->address);
		if (ret < 0) {
			stk8ba50_set_power(data, STK8BA50_MODE_SUSPEND);
			mutex_unlock(&data->lock);
			return -EINVAL;
		}
		*val = sign_extend32(ret >> STK8BA50_DATA_SHIFT, 9);
		stk8ba50_set_power(data, STK8BA50_MODE_SUSPEND);
		mutex_unlock(&data->lock);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = stk8ba50_scale_table[data->range].scale_val;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = stk8ba50_samp_freq_table
				[data->sample_rate_idx].samp_freq;
		*val2 = 0;
		return IIO_VAL_INT;
	}

	return -EINVAL;
}