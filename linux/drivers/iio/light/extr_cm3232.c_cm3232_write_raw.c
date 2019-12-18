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
struct cm3232_chip {struct cm3232_als_info* als_info; } ;
struct cm3232_als_info {int calibscale; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_INT_TIME 128 
 int cm3232_write_als_it (struct cm3232_chip*,int,int) ; 
 struct cm3232_chip* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int cm3232_write_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int val, int val2, long mask)
{
	struct cm3232_chip *chip = iio_priv(indio_dev);
	struct cm3232_als_info *als_info = chip->als_info;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		als_info->calibscale = val;
		return 0;
	case IIO_CHAN_INFO_INT_TIME:
		return cm3232_write_als_it(chip, val, val2);
	}

	return -EINVAL;
}