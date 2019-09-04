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
struct vz89x_data {int* buffer; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 134 
#define  IIO_CHAN_INFO_RAW 133 
#define  IIO_CHAN_INFO_SCALE 132 
#define  IIO_CONCENTRATION 131 
#define  IIO_MOD_CO2 130 
#define  IIO_MOD_VOC 129 
#define  IIO_RESISTANCE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct vz89x_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vz89x_get_measurement (struct vz89x_data*) ; 
 int vz89x_get_resistance_reading (struct vz89x_data*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int vz89x_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan, int *val,
			  int *val2, long mask)
{
	struct vz89x_data *data = iio_priv(indio_dev);
	int ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&data->lock);
		ret = vz89x_get_measurement(data);
		mutex_unlock(&data->lock);

		if (ret)
			return ret;

		switch (chan->type) {
		case IIO_CONCENTRATION:
			*val = data->buffer[chan->address];
			return IIO_VAL_INT;
		case IIO_RESISTANCE:
			ret = vz89x_get_resistance_reading(data, chan, val);
			if (!ret)
				return IIO_VAL_INT;
			break;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_RESISTANCE:
			*val = 10;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->channel2) {
		case IIO_MOD_CO2:
			*val = 44;
			*val2 = 250000;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_MOD_VOC:
			*val = -13;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	}

	return ret;
}