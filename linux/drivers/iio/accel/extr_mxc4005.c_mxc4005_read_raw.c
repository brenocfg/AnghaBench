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
struct mxc4005_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int shift; int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  address; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_ACCEL 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct mxc4005_data* iio_priv (struct iio_dev*) ; 
 int mxc4005_read_axis (struct mxc4005_data*,int /*<<< orphan*/ ) ; 
 int mxc4005_read_scale (struct mxc4005_data*) ; 
 int sign_extend32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxc4005_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mxc4005_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_ACCEL:
			if (iio_buffer_enabled(indio_dev))
				return -EBUSY;

			ret = mxc4005_read_axis(data, chan->address);
			if (ret < 0)
				return ret;
			*val = sign_extend32(ret >> chan->scan_type.shift,
					     chan->scan_type.realbits - 1);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		ret = mxc4005_read_scale(data);
		if (ret < 0)
			return ret;

		*val = 0;
		*val2 = ret;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}