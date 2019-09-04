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
struct iio_chan_spec {scalar_t__ type; } ;
struct ad5421_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5421_REG_DAC_DATA ; 
 int /*<<< orphan*/  AD5421_REG_GAIN ; 
 int /*<<< orphan*/  AD5421_REG_OFFSET ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_CALIBSCALE 131 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 scalar_t__ IIO_CURRENT ; 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  ad5421_get_current_min_max (struct ad5421_state*,unsigned int*,unsigned int*) ; 
 int ad5421_get_offset (struct ad5421_state*) ; 
 int ad5421_read (struct iio_dev*,int /*<<< orphan*/ ) ; 
 struct ad5421_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5421_read_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int *val, int *val2, long m)
{
	struct ad5421_state *st = iio_priv(indio_dev);
	unsigned int min, max;
	int ret;

	if (chan->type != IIO_CURRENT)
		return -EINVAL;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = ad5421_read(indio_dev, AD5421_REG_DAC_DATA);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ad5421_get_current_min_max(st, &min, &max);
		*val = max - min;
		*val2 = (1 << 16) * 1000;
		return IIO_VAL_FRACTIONAL;
	case IIO_CHAN_INFO_OFFSET:
		*val = ad5421_get_offset(st);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBBIAS:
		ret = ad5421_read(indio_dev, AD5421_REG_OFFSET);
		if (ret < 0)
			return ret;
		*val = ret - 32768;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBSCALE:
		ret = ad5421_read(indio_dev, AD5421_REG_GAIN);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	}

	return -EINVAL;
}