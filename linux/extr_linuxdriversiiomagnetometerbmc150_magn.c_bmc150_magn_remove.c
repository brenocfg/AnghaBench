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
struct device {int dummy; } ;
struct bmc150_magn_data {scalar_t__ irq; int /*<<< orphan*/  mutex; scalar_t__ dready_trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_MAGN_POWER_MODE_SUSPEND ; 
 int /*<<< orphan*/  bmc150_magn_set_power_mode (struct bmc150_magn_data*,int /*<<< orphan*/ ,int) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (scalar_t__) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 

int bmc150_magn_remove(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct bmc150_magn_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_put_noidle(dev);

	iio_triggered_buffer_cleanup(indio_dev);

	if (data->irq > 0)
		free_irq(data->irq, data->dready_trig);

	if (data->dready_trig)
		iio_trigger_unregister(data->dready_trig);

	mutex_lock(&data->mutex);
	bmc150_magn_set_power_mode(data, BMC150_MAGN_POWER_MODE_SUSPEND, true);
	mutex_unlock(&data->mutex);

	return 0;
}