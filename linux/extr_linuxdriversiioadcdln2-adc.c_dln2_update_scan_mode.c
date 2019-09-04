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
struct iio_dev {int num_channels; } ;
struct dln2_adc {int /*<<< orphan*/  mutex; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dln2_adc_set_chan_enabled (struct dln2_adc*,int,int) ; 
 int /*<<< orphan*/  dln2_adc_update_demux (struct dln2_adc*) ; 
 struct dln2_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int,unsigned long const*) ; 

__attribute__((used)) static int dln2_update_scan_mode(struct iio_dev *indio_dev,
				 const unsigned long *scan_mask)
{
	struct dln2_adc *dln2 = iio_priv(indio_dev);
	int chan_count = indio_dev->num_channels - 1;
	int ret, i, j;

	mutex_lock(&dln2->mutex);

	for (i = 0; i < chan_count; ++i) {
		ret = dln2_adc_set_chan_enabled(dln2, i,
						test_bit(i, scan_mask));
		if (ret < 0) {
			for (j = 0; j < i; ++j)
				dln2_adc_set_chan_enabled(dln2, j, false);
			mutex_unlock(&dln2->mutex);
			dev_err(&dln2->pdev->dev,
				"Unable to enable ADC channel %d\n", i);
			return -EBUSY;
		}
	}

	dln2_adc_update_demux(dln2);

	mutex_unlock(&dln2->mutex);

	return 0;
}