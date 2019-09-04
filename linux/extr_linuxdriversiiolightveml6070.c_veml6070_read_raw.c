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
struct veml6070_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 struct veml6070_data* iio_priv (struct iio_dev*) ; 
 int veml6070_read (struct veml6070_data*) ; 
 int veml6070_to_uv_index (int) ; 

__attribute__((used)) static int veml6070_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct veml6070_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:
		ret = veml6070_read(data);
		if (ret < 0)
			return ret;
		if (mask == IIO_CHAN_INFO_PROCESSED)
			*val = veml6070_to_uv_index(ret);
		else
			*val = ret;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}