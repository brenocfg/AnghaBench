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
struct iio_channel {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_OFFSET ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_SCALE ; 
#define  IIO_VAL_FRACTIONAL 132 
#define  IIO_VAL_FRACTIONAL_LOG2 131 
#define  IIO_VAL_INT 130 
#define  IIO_VAL_INT_PLUS_MICRO 129 
#define  IIO_VAL_INT_PLUS_NANO 128 
 int div_s64 (int,int) ; 
 int iio_channel_read (struct iio_channel*,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iio_convert_raw_to_processed_unlocked(struct iio_channel *chan,
	int raw, int *processed, unsigned int scale)
{
	int scale_type, scale_val, scale_val2, offset;
	s64 raw64 = raw;
	int ret;

	ret = iio_channel_read(chan, &offset, NULL, IIO_CHAN_INFO_OFFSET);
	if (ret >= 0)
		raw64 += offset;

	scale_type = iio_channel_read(chan, &scale_val, &scale_val2,
					IIO_CHAN_INFO_SCALE);
	if (scale_type < 0) {
		/*
		 * Just pass raw values as processed if no scaling is
		 * available.
		 */
		*processed = raw;
		return 0;
	}

	switch (scale_type) {
	case IIO_VAL_INT:
		*processed = raw64 * scale_val;
		break;
	case IIO_VAL_INT_PLUS_MICRO:
		if (scale_val2 < 0)
			*processed = -raw64 * scale_val;
		else
			*processed = raw64 * scale_val;
		*processed += div_s64(raw64 * (s64)scale_val2 * scale,
				      1000000LL);
		break;
	case IIO_VAL_INT_PLUS_NANO:
		if (scale_val2 < 0)
			*processed = -raw64 * scale_val;
		else
			*processed = raw64 * scale_val;
		*processed += div_s64(raw64 * (s64)scale_val2 * scale,
				      1000000000LL);
		break;
	case IIO_VAL_FRACTIONAL:
		*processed = div_s64(raw64 * (s64)scale_val * scale,
				     scale_val2);
		break;
	case IIO_VAL_FRACTIONAL_LOG2:
		*processed = (raw64 * (s64)scale_val * scale) >> scale_val2;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}