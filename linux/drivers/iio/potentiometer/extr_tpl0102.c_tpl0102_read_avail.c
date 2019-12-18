#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tpl0102_data {TYPE_1__* cfg; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_2__ {int* avail; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int IIO_AVAIL_RANGE ; 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 struct tpl0102_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int tpl0102_read_avail(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      const int **vals, int *type, int *length,
			      long mask)
{
	struct tpl0102_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		*length = ARRAY_SIZE(data->cfg->avail);
		*vals = data->cfg->avail;
		*type = IIO_VAL_INT;
		return IIO_AVAIL_RANGE;
	}

	return -EINVAL;
}