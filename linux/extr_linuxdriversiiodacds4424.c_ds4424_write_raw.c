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
union ds4424_raw_data {int dx; int /*<<< orphan*/  bits; int /*<<< orphan*/  source_bit; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS4424_SINK_I ; 
 int /*<<< orphan*/  DS4424_SOURCE_I ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int S8_MAX ; 
 int S8_MIN ; 
 int ds4424_set_value (struct iio_dev*,int /*<<< orphan*/ ,struct iio_chan_spec const*) ; 

__attribute__((used)) static int ds4424_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	union ds4424_raw_data raw;

	if (val2 != 0)
		return -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val < S8_MIN || val > S8_MAX)
			return -EINVAL;

		if (val > 0) {
			raw.source_bit = DS4424_SOURCE_I;
			raw.dx = val;
		} else {
			raw.source_bit = DS4424_SINK_I;
			raw.dx = -val;
		}

		return ds4424_set_value(indio_dev, raw.bits, chan);

	default:
		return -EINVAL;
	}
}