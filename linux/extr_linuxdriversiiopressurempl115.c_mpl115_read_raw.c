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
struct mpl115_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_PROCESSED 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct mpl115_data* iio_priv (struct iio_dev*) ; 
 int mpl115_comp_pressure (struct mpl115_data*,int*,int*) ; 
 int mpl115_read_temp (struct mpl115_data*) ; 

__attribute__((used)) static int mpl115_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mpl115_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		ret = mpl115_comp_pressure(data, val, val2);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_RAW:
		/* temperature -5.35 C / LSB, 472 LSB is 25 C */
		ret = mpl115_read_temp(data);
		if (ret < 0)
			return ret;
		*val = ret >> 6;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OFFSET:
		*val = -605;
		*val2 = 750000;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SCALE:
		*val = -186;
		*val2 = 915888;
		return IIO_VAL_INT_PLUS_MICRO;
	}
	return -EINVAL;
}