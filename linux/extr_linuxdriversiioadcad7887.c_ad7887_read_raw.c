#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct TYPE_4__ {int shift; int realbits; } ;
struct iio_chan_spec {TYPE_2__ scan_type; int /*<<< orphan*/  address; } ;
struct ad7887_state {TYPE_1__* chip_info; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {int int_vref_mv; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int ad7887_scan_direct (struct ad7887_state*,int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ad7887_state* iio_priv (struct iio_dev*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7887_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	int ret;
	struct ad7887_state *st = iio_priv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		ret = ad7887_scan_direct(st, chan->address);
		iio_device_release_direct_mode(indio_dev);

		if (ret < 0)
			return ret;
		*val = ret >> chan->scan_type.shift;
		*val &= GENMASK(chan->scan_type.realbits - 1, 0);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (st->reg) {
			*val = regulator_get_voltage(st->reg);
			if (*val < 0)
				return *val;
			*val /= 1000;
		} else {
			*val = st->chip_info->int_vref_mv;
		}

		*val2 = chan->scan_type.realbits;

		return IIO_VAL_FRACTIONAL_LOG2;
	}
	return -EINVAL;
}