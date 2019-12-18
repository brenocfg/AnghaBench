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
struct dln2_adc {int sample_period; int trigger_chan; int /*<<< orphan*/  mutex; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int UINT_MAX ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int dln2_adc_set_chan_period (struct dln2_adc*,int,int) ; 
 struct dln2_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dln2_adc_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int val,
			      int val2,
			      long mask)
{
	int ret;
	unsigned int microhertz;
	struct dln2_adc *dln2 = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		microhertz = 1000000 * val + val2;

		mutex_lock(&dln2->mutex);

		dln2->sample_period =
			microhertz ? 1000000000 / microhertz : UINT_MAX;
		if (dln2->sample_period > 65535) {
			dln2->sample_period = 65535;
			dev_warn(&dln2->pdev->dev,
				 "clamping period to 65535ms\n");
		}

		/*
		 * The first requested channel is arbitrated as a shared
		 * trigger source, so only one event is registered with the
		 * DLN. The event handler will then read all enabled channel
		 * values using DLN2_ADC_CHANNEL_GET_ALL_VAL to maintain
		 * synchronization between ADC readings.
		 */
		if (dln2->trigger_chan != -1)
			ret = dln2_adc_set_chan_period(dln2,
				dln2->trigger_chan, dln2->sample_period);
		else
			ret = 0;

		mutex_unlock(&dln2->mutex);

		return ret;

	default:
		return -EINVAL;
	}
}