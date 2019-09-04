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
#define  IIO_CHAN_INFO_CALIBSCALE 130 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_PROCESSED 128 
 int IIO_VAL_INT ; 
 int cm32181_get_lux (struct cm32181_chip*) ; 
 int cm32181_read_als_it (struct cm32181_chip*,int*) ; 
 struct cm32181_chip* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int cm32181_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct cm32181_chip *cm32181 = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		ret = cm32181_get_lux(cm32181);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBSCALE:
		*val = cm32181->calibscale;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		ret = cm32181_read_als_it(cm32181, val2);
		return ret;
	}

	return -EINVAL;
}