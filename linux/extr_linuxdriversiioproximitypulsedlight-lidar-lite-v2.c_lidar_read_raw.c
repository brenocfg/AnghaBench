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
typedef  int u16 ;
struct lidar_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct lidar_data* iio_priv (struct iio_dev*) ; 
 int lidar_get_measurement (struct lidar_data*,int*) ; 

__attribute__((used)) static int lidar_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan,
			  int *val, int *val2, long mask)
{
	struct lidar_data *data = iio_priv(indio_dev);
	int ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW: {
		u16 reg;

		if (iio_device_claim_direct_mode(indio_dev))
			return -EBUSY;

		ret = lidar_get_measurement(data, &reg);
		if (!ret) {
			*val = reg;
			ret = IIO_VAL_INT;
		}
		iio_device_release_direct_mode(indio_dev);
		break;
	}
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 10000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	}

	return ret;
}