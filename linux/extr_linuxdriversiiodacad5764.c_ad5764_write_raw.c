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
typedef  int /*<<< orphan*/  u16 ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int realbits; int shift; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_RAW 128 
 unsigned int ad5764_chan_info_to_reg (struct iio_chan_spec const*,long) ; 
 int ad5764_write (struct iio_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5764_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long info)
{
	const int max_val = (1 << chan->scan_type.realbits);
	unsigned int reg;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		if (val >= max_val || val < 0)
			return -EINVAL;
		val <<= chan->scan_type.shift;
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		if (val >= 128 || val < -128)
			return -EINVAL;
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		if (val >= 32 || val < -32)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	reg = ad5764_chan_info_to_reg(chan, info);
	return ad5764_write(indio_dev, reg, (u16)val);
}