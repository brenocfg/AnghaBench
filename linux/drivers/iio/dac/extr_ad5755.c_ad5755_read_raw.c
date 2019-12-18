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
struct TYPE_2__ {int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;
struct ad5755_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int ad5755_chan_reg_info (struct ad5755_state*,struct iio_chan_spec const*,long,int,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ad5755_get_min_max (struct ad5755_state*,struct iio_chan_spec const*,int*,int*) ; 
 int ad5755_get_offset (struct ad5755_state*,struct iio_chan_spec const*) ; 
 int ad5755_read (struct iio_dev*,unsigned int) ; 
 struct ad5755_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5755_read_raw(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int *val, int *val2, long info)
{
	struct ad5755_state *st = iio_priv(indio_dev);
	unsigned int reg, shift, offset;
	int min, max;
	int ret;

	switch (info) {
	case IIO_CHAN_INFO_SCALE:
		ad5755_get_min_max(st, chan, &min, &max);
		*val = max - min;
		*val2 = chan->scan_type.realbits;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_OFFSET:
		*val = ad5755_get_offset(st, chan);
		return IIO_VAL_INT;
	default:
		ret = ad5755_chan_reg_info(st, chan, info, false,
						&reg, &shift, &offset);
		if (ret)
			return ret;

		ret = ad5755_read(indio_dev, reg);
		if (ret < 0)
			return ret;

		*val = (ret - offset) >> shift;

		return IIO_VAL_INT;
	}

	return -EINVAL;
}