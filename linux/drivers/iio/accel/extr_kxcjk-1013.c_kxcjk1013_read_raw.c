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
struct kxcjk1013_data {size_t range; int /*<<< orphan*/  mutex; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  scan_index; } ;
struct TYPE_2__ {int scale; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 TYPE_1__* KXCJK1013_scale_table ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct kxcjk1013_data* iio_priv (struct iio_dev*) ; 
 int kxcjk1013_get_acc_reg (struct kxcjk1013_data*,int /*<<< orphan*/ ) ; 
 int kxcjk1013_get_odr (struct kxcjk1013_data*,int*,int*) ; 
 int kxcjk1013_set_power_state (struct kxcjk1013_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int kxcjk1013_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan, int *val,
			      int *val2, long mask)
{
	struct kxcjk1013_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&data->mutex);
		if (iio_buffer_enabled(indio_dev))
			ret = -EBUSY;
		else {
			ret = kxcjk1013_set_power_state(data, true);
			if (ret < 0) {
				mutex_unlock(&data->mutex);
				return ret;
			}
			ret = kxcjk1013_get_acc_reg(data, chan->scan_index);
			if (ret < 0) {
				kxcjk1013_set_power_state(data, false);
				mutex_unlock(&data->mutex);
				return ret;
			}
			*val = sign_extend32(ret >> 4, 11);
			ret = kxcjk1013_set_power_state(data, false);
		}
		mutex_unlock(&data->mutex);

		if (ret < 0)
			return ret;

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = KXCJK1013_scale_table[data->range].scale;
		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = kxcjk1013_get_odr(data, val, val2);
		mutex_unlock(&data->mutex);
		return ret;

	default:
		return -EINVAL;
	}
}