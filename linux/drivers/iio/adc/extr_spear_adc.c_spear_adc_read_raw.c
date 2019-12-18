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
typedef  int u32 ;
struct spear_adc_state {int vref_external; int value; int current_clk; int /*<<< orphan*/  completion; int /*<<< orphan*/  avg_samples; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int SPEAR_ADC_DATA_BITS ; 
 int SPEAR_ADC_STATUS_ADC_ENABLE ; 
 int SPEAR_ADC_STATUS_AVG_SAMPLE (int /*<<< orphan*/ ) ; 
 int SPEAR_ADC_STATUS_CHANNEL_NUM (int /*<<< orphan*/ ) ; 
 int SPEAR_ADC_STATUS_START_CONVERSION ; 
 int SPEAR_ADC_STATUS_VREF_INTERNAL ; 
 struct spear_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spear_adc_set_status (struct spear_adc_state*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spear_adc_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val,
			      int *val2,
			      long mask)
{
	struct spear_adc_state *st = iio_priv(indio_dev);
	u32 status;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);

		status = SPEAR_ADC_STATUS_CHANNEL_NUM(chan->channel) |
			SPEAR_ADC_STATUS_AVG_SAMPLE(st->avg_samples) |
			SPEAR_ADC_STATUS_START_CONVERSION |
			SPEAR_ADC_STATUS_ADC_ENABLE;
		if (st->vref_external == 0)
			status |= SPEAR_ADC_STATUS_VREF_INTERNAL;

		spear_adc_set_status(st, status);
		wait_for_completion(&st->completion); /* set by ISR */
		*val = st->value;

		mutex_unlock(&indio_dev->mlock);

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = st->vref_external;
		*val2 = SPEAR_ADC_DATA_BITS;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->current_clk;
		return IIO_VAL_INT;
	}

	return -EINVAL;
}