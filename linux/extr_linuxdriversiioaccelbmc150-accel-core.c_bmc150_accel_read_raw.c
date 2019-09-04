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
struct iio_chan_spec {int const type; } ;
struct bmc150_scale_info {int scale; int /*<<< orphan*/  reg_range; } ;
struct bmc150_accel_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  range; TYPE_1__* chip_info; } ;
struct TYPE_2__ {struct bmc150_scale_info* scale_table; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bmc150_scale_info*) ; 
 int BMC150_ACCEL_TEMP_CENTER_VAL ; 
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_ACCEL 133 
#define  IIO_CHAN_INFO_OFFSET 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SAMP_FREQ 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int bmc150_accel_get_axis (struct bmc150_accel_data*,struct iio_chan_spec const*,int*) ; 
 int bmc150_accel_get_bw (struct bmc150_accel_data*,int*,int*) ; 
 int bmc150_accel_get_temp (struct bmc150_accel_data*,int*) ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct bmc150_accel_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmc150_accel_read_raw(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan,
				 int *val, int *val2, long mask)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_TEMP:
			return bmc150_accel_get_temp(data, val);
		case IIO_ACCEL:
			if (iio_buffer_enabled(indio_dev))
				return -EBUSY;
			else
				return bmc150_accel_get_axis(data, chan, val);
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		if (chan->type == IIO_TEMP) {
			*val = BMC150_ACCEL_TEMP_CENTER_VAL;
			return IIO_VAL_INT;
		} else {
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		switch (chan->type) {
		case IIO_TEMP:
			*val2 = 500000;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_ACCEL:
		{
			int i;
			const struct bmc150_scale_info *si;
			int st_size = ARRAY_SIZE(data->chip_info->scale_table);

			for (i = 0; i < st_size; ++i) {
				si = &data->chip_info->scale_table[i];
				if (si->reg_range == data->range) {
					*val2 = si->scale;
					return IIO_VAL_INT_PLUS_MICRO;
				}
			}
			return -EINVAL;
		}
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = bmc150_accel_get_bw(data, val, val2);
		mutex_unlock(&data->mutex);
		return ret;
	default:
		return -EINVAL;
	}
}