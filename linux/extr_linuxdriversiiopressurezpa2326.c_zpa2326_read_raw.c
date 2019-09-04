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
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int zpa2326_get_frequency (struct iio_dev*) ; 
 int zpa2326_sample_oneshot (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int zpa2326_read_raw(struct iio_dev             *indio_dev,
			    struct iio_chan_spec const *chan,
			    int                        *val,
			    int                        *val2,
			    long                        mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return zpa2326_sample_oneshot(indio_dev, chan->type, val);

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_PRESSURE:
			/*
			 * Pressure resolution is 1/64 Pascal. Scale to kPascal
			 * as required by IIO ABI.
			 */
			*val = 1;
			*val2 = 64000;
			return IIO_VAL_FRACTIONAL;

		case IIO_TEMP:
			/*
			 * Temperature follows the equation:
			 *     Temp[degC] = Tempcode * 0.00649 - 176.83
			 * where:
			 *     Tempcode is composed the raw sampled 16 bits.
			 *
			 * Hence, to produce a temperature in milli-degrees
			 * Celsius according to IIO ABI, we need to apply the
			 * following equation to raw samples:
			 *     Temp[milli degC] = (Tempcode + Offset) * Scale
			 * where:
			 *     Offset = -176.83 / 0.00649
			 *     Scale = 0.00649 * 1000
			 */
			*val = 6;
			*val2 = 490000;
			return IIO_VAL_INT_PLUS_MICRO;

		default:
			return -EINVAL;
		}

	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			*val = -17683000;
			*val2 = 649;
			return IIO_VAL_FRACTIONAL;

		default:
			return -EINVAL;
		}

	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = zpa2326_get_frequency(indio_dev);
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}