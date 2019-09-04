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
struct vl6180_data {int als_it_ms; int als_gain_milli; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 133 
#define  IIO_CHAN_INFO_INT_TIME 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_DISTANCE 129 
#define  IIO_LIGHT 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct vl6180_data* iio_priv (struct iio_dev*) ; 
 int vl6180_measure (struct vl6180_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vl6180_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct vl6180_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = vl6180_measure(data, chan->address);
		if (ret < 0)
			return ret;
		*val = ret;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_INT_TIME:
		*val = data->als_it_ms;
		*val2 = 1000;

		return IIO_VAL_FRACTIONAL;

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_LIGHT:
			/* one ALS count is 0.32 Lux @ gain 1, IT 100 ms */
			*val = 32000; /* 0.32 * 1000 * 100 */
			*val2 = data->als_gain_milli * data->als_it_ms;

			return IIO_VAL_FRACTIONAL;

		case IIO_DISTANCE:
			*val = 0; /* sensor reports mm, scale to meter */
			*val2 = 1000;
			break;
		default:
			return -EINVAL;
		}

		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_HARDWAREGAIN:
		*val = data->als_gain_milli;
		*val2 = 1000;

		return IIO_VAL_FRACTIONAL;

	default:
		return -EINVAL;
	}
}