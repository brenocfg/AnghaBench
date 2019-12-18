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
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int axp20x_adc_offset (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int axp20x_adc_raw (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int axp20x_adc_scale (struct iio_chan_spec const*,int*,int*) ; 

__attribute__((used)) static int axp20x_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan, int *val,
			   int *val2, long mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		return axp20x_adc_offset(indio_dev, chan, val);

	case IIO_CHAN_INFO_SCALE:
		return axp20x_adc_scale(chan, val, val2);

	case IIO_CHAN_INFO_RAW:
		return axp20x_adc_raw(indio_dev, chan, val);

	default:
		return -EINVAL;
	}
}