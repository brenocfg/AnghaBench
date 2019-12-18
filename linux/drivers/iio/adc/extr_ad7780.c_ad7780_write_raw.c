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
struct iio_chan_spec {int dummy; } ;
struct ad7780_state {long long int_vref_mv; unsigned int gain; int /*<<< orphan*/  filter_gpio; int /*<<< orphan*/  odr; int /*<<< orphan*/  gain_gpio; struct ad7780_chip_info* chip_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  realbits; } ;
struct TYPE_4__ {TYPE_1__ scan_type; } ;
struct ad7780_chip_info {TYPE_2__ channel; int /*<<< orphan*/  is_ad778x; } ;

/* Variables and functions */
 int AD7780_FILTER_MIDPOINT ; 
 unsigned int AD7780_GAIN_MIDPOINT ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 unsigned int DIV_ROUND_CLOSEST_ULL (unsigned long long,unsigned int) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/ * ad778x_odr_avail ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ad7780_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7780_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long m)
{
	struct ad7780_state *st = iio_priv(indio_dev);
	const struct ad7780_chip_info *chip_info = st->chip_info;
	unsigned long long vref;
	unsigned int full_scale, gain;

	if (!chip_info->is_ad778x)
		return -EINVAL;

	switch (m) {
	case IIO_CHAN_INFO_SCALE:
		if (val != 0)
			return -EINVAL;

		vref = st->int_vref_mv * 1000000LL;
		full_scale = 1 << (chip_info->channel.scan_type.realbits - 1);
		gain = DIV_ROUND_CLOSEST_ULL(vref, full_scale);
		gain = DIV_ROUND_CLOSEST(gain, val2);
		st->gain = gain;
		if (gain < AD7780_GAIN_MIDPOINT)
			gain = 0;
		else
			gain = 1;
		gpiod_set_value(st->gain_gpio, gain);
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (1000*val + val2/1000 < AD7780_FILTER_MIDPOINT)
			val = 0;
		else
			val = 1;
		st->odr = ad778x_odr_avail[val];
		gpiod_set_value(st->filter_gpio, val);
		break;
	default:
		break;
	}

	return 0;
}