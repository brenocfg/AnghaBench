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
struct ad7192_state {scalar_t__ scale_avail; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__) ; 
 int EINVAL ; 
 int IIO_AVAIL_LIST ; 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT_PLUS_NANO ; 
 struct ad7192_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7192_read_avail(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     const int **vals, int *type, int *length,
			     long mask)
{
	struct ad7192_state *st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		*vals = (int *)st->scale_avail;
		*type = IIO_VAL_INT_PLUS_NANO;
		/* Values are stored in a 2D matrix  */
		*length = ARRAY_SIZE(st->scale_avail) * 2;

		return IIO_AVAIL_LIST;
	}

	return -EINVAL;
}