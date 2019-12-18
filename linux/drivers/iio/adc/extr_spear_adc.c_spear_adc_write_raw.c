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
struct spear_adc_state {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 long IIO_CHAN_INFO_SAMP_FREQ ; 
 int SPEAR_ADC_CLK_MAX ; 
 int SPEAR_ADC_CLK_MIN ; 
 struct spear_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spear_adc_set_clk (struct spear_adc_state*,int) ; 

__attribute__((used)) static int spear_adc_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct spear_adc_state *st = iio_priv(indio_dev);
	int ret = 0;

	if (mask != IIO_CHAN_INFO_SAMP_FREQ)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);

	if ((val < SPEAR_ADC_CLK_MIN) ||
	    (val > SPEAR_ADC_CLK_MAX) ||
	    (val2 != 0)) {
		ret = -EINVAL;
		goto out;
	}

	spear_adc_set_clk(st, val);

out:
	mutex_unlock(&indio_dev->mlock);
	return ret;
}