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
struct TYPE_2__ {int min; int max; } ;
struct ad5758_state {TYPE_1__ out_range; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5758_DAC_INPUT ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int ad5758_spi_reg_read (struct ad5758_state*,int /*<<< orphan*/ ) ; 
 struct ad5758_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5758_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long info)
{
	struct ad5758_state *st = iio_priv(indio_dev);
	int max, min, ret;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = ad5758_spi_reg_read(st, AD5758_DAC_INPUT);
		mutex_unlock(&st->lock);
		if (ret < 0)
			return ret;

		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		min = st->out_range.min;
		max = st->out_range.max;
		*val = (max - min) / 1000;
		*val2 = 16;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_OFFSET:
		min = st->out_range.min;
		max = st->out_range.max;
		*val = ((min * (1 << 16)) / (max - min)) / 1000;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}