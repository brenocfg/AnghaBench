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
struct iio_chan_spec {size_t address; TYPE_1__ scan_type; } ;
struct ad5449 {int* dac_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5449_CMD_LOAD_AND_UPDATE (size_t) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int ad5449_write (struct iio_dev*,int /*<<< orphan*/ ,int) ; 
 struct ad5449* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5449_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long info)
{
	struct ad5449 *st = iio_priv(indio_dev);
	int ret;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		if (val < 0 || val >= (1 << chan->scan_type.realbits))
			return -EINVAL;

		ret = ad5449_write(indio_dev,
			AD5449_CMD_LOAD_AND_UPDATE(chan->address),
			val << chan->scan_type.shift);
		if (ret == 0)
			st->dac_cache[chan->address] = val;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}