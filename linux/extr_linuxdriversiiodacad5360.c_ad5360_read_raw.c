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
struct TYPE_2__ {int shift; int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  channel; int /*<<< orphan*/  address; } ;
struct ad5360_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5360_READBACK_GAIN ; 
 int /*<<< orphan*/  AD5360_READBACK_OFFSET ; 
 int /*<<< orphan*/  AD5360_READBACK_SF ; 
 int /*<<< orphan*/  AD5360_READBACK_X1A ; 
 int /*<<< orphan*/  AD5360_REG_SF_OFS (unsigned int) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_CALIBSCALE 131 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int ad5360_get_channel_vref (struct ad5360_state*,int /*<<< orphan*/ ) ; 
 unsigned int ad5360_get_channel_vref_index (struct ad5360_state*,int /*<<< orphan*/ ) ; 
 int ad5360_read (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad5360_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5360_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad5360_state *st = iio_priv(indio_dev);
	unsigned int ofs_index;
	int scale_uv;
	int ret;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = ad5360_read(indio_dev, AD5360_READBACK_X1A,
			chan->address);
		if (ret < 0)
			return ret;
		*val = ret >> chan->scan_type.shift;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		scale_uv = ad5360_get_channel_vref(st, chan->channel);
		if (scale_uv < 0)
			return scale_uv;

		/* vout = 4 * vref * dac_code */
		*val = scale_uv * 4 / 1000;
		*val2 = chan->scan_type.realbits;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_CALIBBIAS:
		ret = ad5360_read(indio_dev, AD5360_READBACK_OFFSET,
			chan->address);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBSCALE:
		ret = ad5360_read(indio_dev, AD5360_READBACK_GAIN,
			chan->address);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OFFSET:
		ofs_index = ad5360_get_channel_vref_index(st, chan->channel);
		ret = ad5360_read(indio_dev, AD5360_READBACK_SF,
			AD5360_REG_SF_OFS(ofs_index));
		if (ret < 0)
			return ret;

		ret <<= (chan->scan_type.realbits - 14);
		*val = -ret;
		return IIO_VAL_INT;
	}

	return -EINVAL;
}