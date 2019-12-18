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
struct sun4i_gpadc_iio {unsigned int fifo_data_irq; int adc_data; int temp_data; int /*<<< orphan*/  mutex; int /*<<< orphan*/  completion; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  disable_irq (unsigned int) ; 
 int /*<<< orphan*/  enable_irq (unsigned int) ; 
 struct sun4i_gpadc_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int sun4i_prepare_for_irq (struct iio_dev*,int,unsigned int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_gpadc_read(struct iio_dev *indio_dev, int channel, int *val,
			    unsigned int irq)
{
	struct sun4i_gpadc_iio *info = iio_priv(indio_dev);
	int ret;

	mutex_lock(&info->mutex);

	ret = sun4i_prepare_for_irq(indio_dev, channel, irq);
	if (ret)
		goto err;

	enable_irq(irq);

	/*
	 * The temperature sensor throws an interruption periodically (currently
	 * set at periods of ~0.6s in sun4i_gpadc_runtime_resume). A 1s delay
	 * makes sure an interruption occurs in normal conditions. If it doesn't
	 * occur, then there is a timeout.
	 */
	if (!wait_for_completion_timeout(&info->completion,
					 msecs_to_jiffies(1000))) {
		ret = -ETIMEDOUT;
		goto err;
	}

	if (irq == info->fifo_data_irq)
		*val = info->adc_data;
	else
		*val = info->temp_data;

	ret = 0;
	pm_runtime_mark_last_busy(indio_dev->dev.parent);

err:
	pm_runtime_put_autosuspend(indio_dev->dev.parent);
	disable_irq(irq);
	mutex_unlock(&info->mutex);

	return ret;
}