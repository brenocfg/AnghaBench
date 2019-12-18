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
struct iio_chan_spec {int dummy; } ;
struct dpot_dac {long long max_ohms; int /*<<< orphan*/  vref; int /*<<< orphan*/  dpot; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SCALE 131 
#define  IIO_VAL_FRACTIONAL 130 
#define  IIO_VAL_FRACTIONAL_LOG2 129 
#define  IIO_VAL_INT 128 
 int /*<<< orphan*/  do_div (unsigned long long,long long) ; 
 struct dpot_dac* iio_priv (struct iio_dev*) ; 
 int iio_read_channel_raw (int /*<<< orphan*/ ,int*) ; 
 int iio_read_channel_scale (int /*<<< orphan*/ ,int*,int*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpot_dac_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct dpot_dac *dac = iio_priv(indio_dev);
	int ret;
	unsigned long long tmp;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return iio_read_channel_raw(dac->dpot, val);

	case IIO_CHAN_INFO_SCALE:
		ret = iio_read_channel_scale(dac->dpot, val, val2);
		switch (ret) {
		case IIO_VAL_FRACTIONAL_LOG2:
			tmp = *val * 1000000000LL;
			do_div(tmp, dac->max_ohms);
			tmp *= regulator_get_voltage(dac->vref) / 1000;
			do_div(tmp, 1000000000LL);
			*val = tmp;
			return ret;
		case IIO_VAL_INT:
			/*
			 * Convert integer scale to fractional scale by
			 * setting the denominator (val2) to one, and...
			 */
			*val2 = 1;
			ret = IIO_VAL_FRACTIONAL;
			/* fall through */
		case IIO_VAL_FRACTIONAL:
			*val *= regulator_get_voltage(dac->vref) / 1000;
			*val2 *= dac->max_ohms;
			break;
		}

		return ret;
	}

	return -EINVAL;
}