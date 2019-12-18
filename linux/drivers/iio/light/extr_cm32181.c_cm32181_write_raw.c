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
struct cm32181_chip {int calibscale; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_INT_TIME 128 
 int cm32181_write_als_it (struct cm32181_chip*,int) ; 
 struct cm32181_chip* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int cm32181_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct cm32181_chip *cm32181 = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		cm32181->calibscale = val;
		return val;
	case IIO_CHAN_INFO_INT_TIME:
		ret = cm32181_write_als_it(cm32181, val2);
		return ret;
	}

	return -EINVAL;
}