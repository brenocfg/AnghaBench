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
struct isl29501_private {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_INT_TIME 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 struct isl29501_private* iio_priv (struct iio_dev*) ; 
 int isl29501_set_calibbias (struct isl29501_private*,struct iio_chan_spec const*,int) ; 
 int isl29501_set_freq (struct isl29501_private*,int,int) ; 
 int isl29501_set_inttime (struct isl29501_private*,int,int) ; 
 int isl29501_set_raw (struct isl29501_private*,struct iio_chan_spec const*,int) ; 
 int isl29501_set_scale (struct isl29501_private*,struct iio_chan_spec const*,int,int) ; 

__attribute__((used)) static int isl29501_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int val, int val2, long mask)
{
	struct isl29501_private *isl29501 = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return isl29501_set_raw(isl29501, chan, val);
	case IIO_CHAN_INFO_INT_TIME:
		return isl29501_set_inttime(isl29501, val, val2);
	case IIO_CHAN_INFO_SAMP_FREQ:
		return isl29501_set_freq(isl29501, val, val2);
	case IIO_CHAN_INFO_SCALE:
		return isl29501_set_scale(isl29501, chan, val, val2);
	case IIO_CHAN_INFO_CALIBBIAS:
		return isl29501_set_calibbias(isl29501, chan, val);
	default:
		return -EINVAL;
	}
}