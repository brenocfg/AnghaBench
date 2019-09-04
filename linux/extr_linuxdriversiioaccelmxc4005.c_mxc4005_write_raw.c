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
struct mxc4005_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 128 
 struct mxc4005_data* iio_priv (struct iio_dev*) ; 
 int mxc4005_set_scale (struct mxc4005_data*,int) ; 

__attribute__((used)) static int mxc4005_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct mxc4005_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		if (val != 0)
			return -EINVAL;

		return mxc4005_set_scale(data, val2);
	default:
		return -EINVAL;
	}
}