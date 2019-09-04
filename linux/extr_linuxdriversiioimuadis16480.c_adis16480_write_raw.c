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
#define  IIO_CHAN_INFO_CALIBBIAS 131 
#define  IIO_CHAN_INFO_CALIBSCALE 130 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int adis16480_set_calibbias (struct iio_dev*,struct iio_chan_spec const*,int) ; 
 int adis16480_set_calibscale (struct iio_dev*,struct iio_chan_spec const*,int) ; 
 int adis16480_set_filter_freq (struct iio_dev*,struct iio_chan_spec const*,int) ; 
 int adis16480_set_freq (struct iio_dev*,int,int) ; 

__attribute__((used)) static int adis16480_write_raw(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int val, int val2, long info)
{
	switch (info) {
	case IIO_CHAN_INFO_CALIBBIAS:
		return adis16480_set_calibbias(indio_dev, chan, val);
	case IIO_CHAN_INFO_CALIBSCALE:
		return adis16480_set_calibscale(indio_dev, chan, val);
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		return adis16480_set_filter_freq(indio_dev, chan, val);
	case IIO_CHAN_INFO_SAMP_FREQ:
		return adis16480_set_freq(indio_dev, val, val2);

	default:
		return -EINVAL;
	}
}