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
struct max1363_state {int vref_uv; TYPE_1__* chip_info; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_2__ {int bits; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 struct max1363_state* iio_priv (struct iio_dev*) ; 
 int max1363_read_single_chan (struct iio_dev*,struct iio_chan_spec const*,int*,long) ; 

__attribute__((used)) static int max1363_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val,
			    int *val2,
			    long m)
{
	struct max1363_state *st = iio_priv(indio_dev);
	int ret;

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = max1363_read_single_chan(indio_dev, chan, val, m);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = st->vref_uv / 1000;
		*val2 = st->chip_info->bits;
		return IIO_VAL_FRACTIONAL_LOG2;
	default:
		return -EINVAL;
	}
	return 0;
}