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
struct tsl2772_chip {size_t id; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int IIO_AVAIL_LIST ; 
 int IIO_AVAIL_RANGE ; 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_INT_TIME 128 
 int /*<<< orphan*/  IIO_INTENSITY ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int* tsl2772_int_calibscale_avail ; 
 int** tsl2772_int_time_avail ; 
 int* tsl2772_prox_calibscale_avail ; 

__attribute__((used)) static int tsl2772_read_avail(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      const int **vals, int *type, int *length,
			      long mask)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->type == IIO_INTENSITY) {
			*length = ARRAY_SIZE(tsl2772_int_calibscale_avail);
			*vals = tsl2772_int_calibscale_avail;
		} else {
			*length = ARRAY_SIZE(tsl2772_prox_calibscale_avail);
			*vals = tsl2772_prox_calibscale_avail;
		}
		*type = IIO_VAL_INT;
		return IIO_AVAIL_LIST;
	case IIO_CHAN_INFO_INT_TIME:
		*length = ARRAY_SIZE(tsl2772_int_time_avail[chip->id]);
		*vals = tsl2772_int_time_avail[chip->id];
		*type = IIO_VAL_INT_PLUS_MICRO;
		return IIO_AVAIL_RANGE;
	}

	return -EINVAL;
}