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
typedef  int /*<<< orphan*/  u8 ;
struct kmx61_data {size_t range; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int shift; int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {int const type; int /*<<< orphan*/  address; TYPE_1__ scan_type; int /*<<< orphan*/  scan_index; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SAMP_FREQ 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_MAGN 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  KMX61_ACC_XOUT_L ; 
 int /*<<< orphan*/  KMX61_MAG_XOUT_L ; 
 struct kmx61_data* kmx61_get_data (struct iio_dev*) ; 
 int kmx61_get_odr (struct kmx61_data*,int*,int*,int /*<<< orphan*/ ) ; 
 int kmx61_read_measurement (struct kmx61_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kmx61_set_power_state (struct kmx61_data*,int,int /*<<< orphan*/ ) ; 
 int* kmx61_uscale_table ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmx61_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan, int *val,
			  int *val2, long mask)
{
	int ret;
	u8 base_reg;
	struct kmx61_data *data = kmx61_get_data(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_ACCEL:
			base_reg = KMX61_ACC_XOUT_L;
			break;
		case IIO_MAGN:
			base_reg = KMX61_MAG_XOUT_L;
			break;
		default:
			return -EINVAL;
		}
		mutex_lock(&data->lock);

		ret = kmx61_set_power_state(data, true, chan->address);
		if (ret) {
			mutex_unlock(&data->lock);
			return ret;
		}

		ret = kmx61_read_measurement(data, base_reg, chan->scan_index);
		if (ret < 0) {
			kmx61_set_power_state(data, false, chan->address);
			mutex_unlock(&data->lock);
			return ret;
		}
		*val = sign_extend32(ret >> chan->scan_type.shift,
				     chan->scan_type.realbits - 1);
		ret = kmx61_set_power_state(data, false, chan->address);

		mutex_unlock(&data->lock);
		if (ret)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ACCEL:
			*val = 0;
			*val2 = kmx61_uscale_table[data->range];
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_MAGN:
			/* 14 bits res, 1465 microGauss per magn count */
			*val = 0;
			*val2 = 1465;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (chan->type != IIO_ACCEL && chan->type != IIO_MAGN)
			return -EINVAL;

		mutex_lock(&data->lock);
		ret = kmx61_get_odr(data, val, val2, chan->address);
		mutex_unlock(&data->lock);
		if (ret)
			return -EINVAL;
		return IIO_VAL_INT_PLUS_MICRO;
	}
	return -EINVAL;
}