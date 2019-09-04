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
 long IIO_CHAN_INFO_SAMP_FREQ ; 
 int zpa2326_set_frequency (struct iio_dev*,int) ; 

__attribute__((used)) static int zpa2326_write_raw(struct iio_dev             *indio_dev,
			     const struct iio_chan_spec *chan,
			     int                         val,
			     int                         val2,
			     long                        mask)
{
	if ((mask != IIO_CHAN_INFO_SAMP_FREQ) || val2)
		return -EINVAL;

	return zpa2326_set_frequency(indio_dev, val);
}