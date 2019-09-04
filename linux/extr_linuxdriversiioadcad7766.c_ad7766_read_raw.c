#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_4__ {int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;
struct ad7766 {TYPE_2__* chip_info; int /*<<< orphan*/  mclk; TYPE_3__* reg; } ;
struct TYPE_6__ {struct regulator* consumer; } ;
struct TYPE_5__ {int decimation_factor; } ;

/* Variables and functions */
 size_t AD7766_SUPPLY_VREF ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct ad7766* iio_priv (struct iio_dev*) ; 
 int regulator_get_voltage (struct regulator*) ; 

__attribute__((used)) static int ad7766_read_raw(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int *val, int *val2, long info)
{
	struct ad7766 *ad7766 = iio_priv(indio_dev);
	struct regulator *vref = ad7766->reg[AD7766_SUPPLY_VREF].consumer;
	int scale_uv;

	switch (info) {
	case IIO_CHAN_INFO_SCALE:
		scale_uv = regulator_get_voltage(vref);
		if (scale_uv < 0)
			return scale_uv;
		*val = scale_uv / 1000;
		*val2 = chan->scan_type.realbits;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = clk_get_rate(ad7766->mclk) /
			ad7766->chip_info->decimation_factor;
		return IIO_VAL_INT;
	}
	return -EINVAL;
}