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
struct TYPE_2__ {int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  address; } ;
struct ad7791_state {int mode; unsigned int filter; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7791_CH_AVDD_MONITOR ; 
 unsigned int AD7791_FILTER_RATE_MASK ; 
 int AD7791_MODE_UNIPOLAR ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int** ad7791_sample_freq_avail ; 
 int ad_sigma_delta_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 struct ad7791_state* iio_priv (struct iio_dev*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7791_read_raw(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int *val, int *val2, long info)
{
	struct ad7791_state *st = iio_priv(indio_dev);
	bool unipolar = !!(st->mode & AD7791_MODE_UNIPOLAR);
	unsigned int rate;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		return ad_sigma_delta_single_conversion(indio_dev, chan, val);
	case IIO_CHAN_INFO_OFFSET:
		/**
		 * Unipolar: 0 to VREF
		 * Bipolar -VREF to VREF
		 **/
		if (unipolar)
			*val = 0;
		else
			*val = -(1 << (chan->scan_type.realbits - 1));
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		/* The monitor channel uses an internal reference. */
		if (chan->address == AD7791_CH_AVDD_MONITOR) {
			/*
			 * The signal is attenuated by a factor of 5 and
			 * compared against a 1.17V internal reference.
			 */
			*val = 1170 * 5;
		} else {
			int voltage_uv;

			voltage_uv = regulator_get_voltage(st->reg);
			if (voltage_uv < 0)
				return voltage_uv;

			*val = voltage_uv / 1000;
		}
		if (unipolar)
			*val2 = chan->scan_type.realbits;
		else
			*val2 = chan->scan_type.realbits - 1;

		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_SAMP_FREQ:
		rate = st->filter & AD7791_FILTER_RATE_MASK;
		*val = ad7791_sample_freq_avail[rate][0];
		*val2 = ad7791_sample_freq_avail[rate][1];
		return IIO_VAL_INT_PLUS_MICRO;
	}

	return -EINVAL;
}