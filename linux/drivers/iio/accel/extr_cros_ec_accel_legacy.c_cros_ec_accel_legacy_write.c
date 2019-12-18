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
 long IIO_CHAN_INFO_CALIBBIAS ; 

__attribute__((used)) static int cros_ec_accel_legacy_write(struct iio_dev *indio_dev,
				      struct iio_chan_spec const *chan,
				      int val, int val2, long mask)
{
	/*
	 * Do nothing but don't return an error code to allow calibration
	 * script to work.
	 */
	if (mask == IIO_CHAN_INFO_CALIBBIAS)
		return 0;

	return -EINVAL;
}