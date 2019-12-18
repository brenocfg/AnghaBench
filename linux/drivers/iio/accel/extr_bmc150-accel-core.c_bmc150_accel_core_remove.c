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
struct bmc150_accel_data {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_ACCEL_SLEEP_MODE_DEEP_SUSPEND ; 
 scalar_t__ BMC150_ACCEL_TRIGGERS ; 
 int /*<<< orphan*/  bmc150_accel_set_mode (struct bmc150_accel_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmc150_accel_unregister_triggers (struct bmc150_accel_data*,scalar_t__) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct bmc150_accel_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 

int bmc150_accel_core_remove(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct bmc150_accel_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_put_noidle(dev);

	bmc150_accel_unregister_triggers(data, BMC150_ACCEL_TRIGGERS - 1);

	iio_triggered_buffer_cleanup(indio_dev);

	mutex_lock(&data->mutex);
	bmc150_accel_set_mode(data, BMC150_ACCEL_SLEEP_MODE_DEEP_SUSPEND, 0);
	mutex_unlock(&data->mutex);

	return 0;
}