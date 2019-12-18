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
struct vl53l0x_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 scalar_t__ IIO_DISTANCE ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct vl53l0x_data* iio_priv (struct iio_dev*) ; 
 int vl53l0x_read_proximity (struct vl53l0x_data*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int vl53l0x_read_raw(struct iio_dev *indio_dev,
			    const struct iio_chan_spec *chan,
			    int *val, int *val2, long mask)
{
	struct vl53l0x_data *data = iio_priv(indio_dev);
	int ret;

	if (chan->type != IIO_DISTANCE)
		return -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = vl53l0x_read_proximity(data, chan, val);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 1000;

		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}