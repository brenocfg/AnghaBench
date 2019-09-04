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
struct iio_chan_spec {size_t address; } ;
struct ak8975_data {int* raw_to_gauss; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int ak8975_read_axis (struct iio_dev*,size_t,int*) ; 
 struct ak8975_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ak8975_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2,
			   long mask)
{
	struct ak8975_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return ak8975_read_axis(indio_dev, chan->address, val);
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = data->raw_to_gauss[chan->address];
		return IIO_VAL_INT_PLUS_MICRO;
	}
	return -EINVAL;
}