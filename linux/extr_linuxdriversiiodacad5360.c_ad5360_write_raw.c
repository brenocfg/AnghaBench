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
struct TYPE_2__ {int realbits; int /*<<< orphan*/  shift; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; TYPE_1__ scan_type; int /*<<< orphan*/  address; } ;
struct ad5360_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5360_CMD_SPECIAL_FUNCTION ; 
 int /*<<< orphan*/  AD5360_CMD_WRITE_DATA ; 
 int /*<<< orphan*/  AD5360_CMD_WRITE_GAIN ; 
 int /*<<< orphan*/  AD5360_CMD_WRITE_OFFSET ; 
 int /*<<< orphan*/  AD5360_REG_SF_OFS (unsigned int) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 131 
#define  IIO_CHAN_INFO_CALIBSCALE 130 
#define  IIO_CHAN_INFO_OFFSET 129 
#define  IIO_CHAN_INFO_RAW 128 
 unsigned int ad5360_get_channel_vref_index (struct ad5360_state*,int /*<<< orphan*/ ) ; 
 int ad5360_write (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ad5360_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5360_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct ad5360_state *st = iio_priv(indio_dev);
	int max_val = (1 << chan->scan_type.realbits);
	unsigned int ofs_index;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val >= max_val || val < 0)
			return -EINVAL;

		return ad5360_write(indio_dev, AD5360_CMD_WRITE_DATA,
				 chan->address, val, chan->scan_type.shift);

	case IIO_CHAN_INFO_CALIBBIAS:
		if (val >= max_val || val < 0)
			return -EINVAL;

		return ad5360_write(indio_dev, AD5360_CMD_WRITE_OFFSET,
				 chan->address, val, chan->scan_type.shift);

	case IIO_CHAN_INFO_CALIBSCALE:
		if (val >= max_val || val < 0)
			return -EINVAL;

		return ad5360_write(indio_dev, AD5360_CMD_WRITE_GAIN,
				 chan->address, val, chan->scan_type.shift);

	case IIO_CHAN_INFO_OFFSET:
		if (val <= -max_val || val > 0)
			return -EINVAL;

		val = -val;

		/* offset is supposed to have the same scale as raw, but it
		 * is always 14bits wide, so on a chip where the raw value has
		 * more bits, we need to shift offset. */
		val >>= (chan->scan_type.realbits - 14);

		/* There is one DAC offset register per vref. Changing one
		 * channels offset will also change the offset for all other
		 * channels which share the same vref supply. */
		ofs_index = ad5360_get_channel_vref_index(st, chan->channel);
		return ad5360_write(indio_dev, AD5360_CMD_SPECIAL_FUNCTION,
				 AD5360_REG_SF_OFS(ofs_index), val, 0);
	default:
		break;
	}

	return -EINVAL;
}