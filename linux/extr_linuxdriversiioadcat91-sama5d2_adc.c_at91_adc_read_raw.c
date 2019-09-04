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
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  differential; } ;
struct at91_adc_state {int vref_uv; int oversampling_ratio; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int at91_adc_get_sample_freq (struct at91_adc_state*) ; 
 int at91_adc_read_info_raw (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int at91_adc_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct at91_adc_state *st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return at91_adc_read_info_raw(indio_dev, chan, val);
	case IIO_CHAN_INFO_SCALE:
		*val = st->vref_uv / 1000;
		if (chan->differential)
			*val *= 2;
		*val2 = chan->scan_type.realbits;
		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = at91_adc_get_sample_freq(st);
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = st->oversampling_ratio;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}