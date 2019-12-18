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
struct TYPE_2__ {int realbits; int shift; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  address; } ;
struct ad5380_state {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5380_REG_OFFSET (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_RAW 128 
 int /*<<< orphan*/  ad5380_info_to_reg (struct iio_chan_spec const*,long) ; 
 struct ad5380_state* iio_priv (struct iio_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad5380_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long info)
{
	const unsigned int max_val = (1 << chan->scan_type.realbits);
	struct ad5380_state *st = iio_priv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_CALIBSCALE:
		if (val >= max_val || val < 0)
			return -EINVAL;

		return regmap_write(st->regmap,
			ad5380_info_to_reg(chan, info),
			val << chan->scan_type.shift);
	case IIO_CHAN_INFO_CALIBBIAS:
		val += (1 << chan->scan_type.realbits) / 2;
		if (val >= max_val || val < 0)
			return -EINVAL;

		return regmap_write(st->regmap,
			AD5380_REG_OFFSET(chan->address),
			val << chan->scan_type.shift);
	default:
		break;
	}
	return -EINVAL;
}