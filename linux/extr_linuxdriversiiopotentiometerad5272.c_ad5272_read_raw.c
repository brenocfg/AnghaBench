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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct ad5272_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {int shift; int kohms; int max_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5272_RDAC_RD ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int ad5272_read (struct ad5272_data*,int /*<<< orphan*/ ,int*) ; 
 struct ad5272_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5272_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct ad5272_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW: {
		ret = ad5272_read(data, AD5272_RDAC_RD, val);
		*val = *val >> data->cfg->shift;
		return ret ? ret : IIO_VAL_INT;
	}
	case IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = data->cfg->max_pos;
		return IIO_VAL_FRACTIONAL;
	}

	return -EINVAL;
}