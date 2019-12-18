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

/* Variables and functions */
 int /*<<< orphan*/  AD5421_REG_DAC_DATA ; 
 int /*<<< orphan*/  AD5421_REG_GAIN ; 
 int /*<<< orphan*/  AD5421_REG_OFFSET ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_RAW 128 
 int ad5421_write (struct iio_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad5421_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	const unsigned int max_val = 1 << 16;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val >= max_val || val < 0)
			return -EINVAL;

		return ad5421_write(indio_dev, AD5421_REG_DAC_DATA, val);
	case IIO_CHAN_INFO_CALIBBIAS:
		val += 32768;
		if (val >= max_val || val < 0)
			return -EINVAL;

		return ad5421_write(indio_dev, AD5421_REG_OFFSET, val);
	case IIO_CHAN_INFO_CALIBSCALE:
		if (val >= max_val || val < 0)
			return -EINVAL;

		return ad5421_write(indio_dev, AD5421_REG_GAIN, val);
	default:
		break;
	}

	return -EINVAL;
}