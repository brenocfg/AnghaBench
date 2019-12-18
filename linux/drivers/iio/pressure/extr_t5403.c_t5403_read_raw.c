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
struct t5403_data {size_t mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 131 
#define  IIO_CHAN_INFO_PROCESSED 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct t5403_data* iio_priv (struct iio_dev*) ; 
 int t5403_comp_pressure (struct t5403_data*,int*,int*) ; 
 int t5403_comp_temp (struct t5403_data*,int*) ; 
 int* t5403_pressure_conv_ms ; 

__attribute__((used)) static int t5403_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan,
			  int *val, int *val2, long mask)
{
	struct t5403_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_PRESSURE:
			ret = t5403_comp_pressure(data, val, val2);
			if (ret < 0)
				return ret;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			ret = t5403_comp_temp(data, val);
			if (ret < 0)
				return ret;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
	    }
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = t5403_pressure_conv_ms[data->mode] * 1000;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}