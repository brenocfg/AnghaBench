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
struct iio_chan_spec {int dummy; } ;
struct TYPE_2__ {int min_sample_rate; int max_sample_rate; } ;
struct at91_adc_state {int oversampling_ratio; TYPE_1__ soc_info; } ;

/* Variables and functions */
 int AT91_OSR_16SAMPLES ; 
 int AT91_OSR_1SAMPLES ; 
 int AT91_OSR_4SAMPLES ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int /*<<< orphan*/  at91_adc_config_emr (struct at91_adc_state*) ; 
 int /*<<< orphan*/  at91_adc_setup_samp_freq (struct at91_adc_state*,int) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int at91_adc_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int val, int val2, long mask)
{
	struct at91_adc_state *st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		if ((val != AT91_OSR_1SAMPLES) && (val != AT91_OSR_4SAMPLES) &&
		    (val != AT91_OSR_16SAMPLES))
			return -EINVAL;
		/* if no change, optimize out */
		if (val == st->oversampling_ratio)
			return 0;
		st->oversampling_ratio = val;
		/* update ratio */
		at91_adc_config_emr(st);
		return 0;
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (val < st->soc_info.min_sample_rate ||
		    val > st->soc_info.max_sample_rate)
			return -EINVAL;

		at91_adc_setup_samp_freq(st, val);
		return 0;
	default:
		return -EINVAL;
	};
}