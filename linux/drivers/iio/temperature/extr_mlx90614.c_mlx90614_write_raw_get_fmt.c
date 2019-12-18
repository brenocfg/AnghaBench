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
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBEMISSIVITY 129 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 128 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 

__attribute__((used)) static int mlx90614_write_raw_get_fmt(struct iio_dev *indio_dev,
				     struct iio_chan_spec const *channel,
				     long mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_CALIBEMISSIVITY:
		return IIO_VAL_INT_PLUS_NANO;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}