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
typedef  int u64 ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int shift; int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  address; } ;
struct ad5791_state {int vref_mv; int /*<<< orphan*/  vref_neg_mv; } ;

/* Variables and functions */
 int AD5791_DAC_MASK ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int ad5791_spi_read (struct ad5791_state*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct ad5791_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5791_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad5791_state *st = iio_priv(indio_dev);
	u64 val64;
	int ret;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = ad5791_spi_read(st, chan->address, val);
		if (ret)
			return ret;
		*val &= AD5791_DAC_MASK;
		*val >>= chan->scan_type.shift;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = (1 << chan->scan_type.realbits) - 1;
		return IIO_VAL_FRACTIONAL;
	case IIO_CHAN_INFO_OFFSET:
		val64 = (((u64)st->vref_neg_mv) << chan->scan_type.realbits);
		do_div(val64, st->vref_mv);
		*val = -val64;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}

}