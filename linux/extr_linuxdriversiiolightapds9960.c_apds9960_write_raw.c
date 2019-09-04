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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct apds9960_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 int apds9960_set_als_gain (struct apds9960_data*,int) ; 
 int apds9960_set_it_time (struct apds9960_data*,int) ; 
 int apds9960_set_pxs_gain (struct apds9960_data*,int) ; 
 struct apds9960_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int apds9960_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct apds9960_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		/* RGB + ALS sensors only have int time */
		switch (chan->type) {
		case IIO_INTENSITY:
			if (val != 0)
				return -EINVAL;
			return apds9960_set_it_time(data, val2);
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		if (val2 != 0)
			return -EINVAL;
		switch (chan->type) {
		case IIO_PROXIMITY:
			return apds9960_set_pxs_gain(data, val);
		case IIO_INTENSITY:
			return apds9960_set_als_gain(data, val);
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	};

	return 0;
}