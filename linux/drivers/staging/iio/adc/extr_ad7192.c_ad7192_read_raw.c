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
struct TYPE_2__ {int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {int const type; TYPE_1__ scan_type; } ;
struct ad7192_state {int conf; int** scale_avail; int fclk; int f_order; int /*<<< orphan*/  mode; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t AD7192_CONF_GAIN (int) ; 
 int AD7192_CONF_UNIPOLAR ; 
 int AD7192_MODE_RATE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 134 
#define  IIO_CHAN_INFO_OFFSET 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_TEMP 129 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
#define  IIO_VOLTAGE 128 
 int ad7192_get_3db_filter_freq (struct ad7192_state*) ; 
 int ad7192_get_temp_scale (int) ; 
 int ad_sigma_delta_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 struct ad7192_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7192_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct ad7192_state *st = iio_priv(indio_dev);
	bool unipolar = !!(st->conf & AD7192_CONF_UNIPOLAR);

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		return ad_sigma_delta_single_conversion(indio_dev, chan, val);
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			mutex_lock(&st->lock);
			*val = st->scale_avail[AD7192_CONF_GAIN(st->conf)][0];
			*val2 = st->scale_avail[AD7192_CONF_GAIN(st->conf)][1];
			mutex_unlock(&st->lock);
			return IIO_VAL_INT_PLUS_NANO;
		case IIO_TEMP:
			*val = 0;
			*val2 = 1000000000 / ad7192_get_temp_scale(unipolar);
			return IIO_VAL_INT_PLUS_NANO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		if (!unipolar)
			*val = -(1 << (chan->scan_type.realbits - 1));
		else
			*val = 0;
		/* Kelvin to Celsius */
		if (chan->type == IIO_TEMP)
			*val -= 273 * ad7192_get_temp_scale(unipolar);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->fclk /
			(st->f_order * 1024 * AD7192_MODE_RATE(st->mode));
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		*val = ad7192_get_3db_filter_freq(st);
		*val2 = 1000;
		return IIO_VAL_FRACTIONAL;
	}

	return -EINVAL;
}