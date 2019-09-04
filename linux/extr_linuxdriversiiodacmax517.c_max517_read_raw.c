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
struct max517_data {int* vref_mv; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 struct max517_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int max517_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct max517_data *data = iio_priv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_SCALE:
		/* Corresponds to Vref / 2^(bits) */
		*val = data->vref_mv[chan->channel];
		*val2 = 8;
		return IIO_VAL_FRACTIONAL_LOG2;
	default:
		break;
	}
	return -EINVAL;
}