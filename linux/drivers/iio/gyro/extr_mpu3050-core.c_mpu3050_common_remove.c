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
struct mpu3050 {scalar_t__ irq; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct mpu3050*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  mpu3050_power_down (struct mpu3050*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 

int mpu3050_common_remove(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct mpu3050 *mpu3050 = iio_priv(indio_dev);

	pm_runtime_get_sync(dev);
	pm_runtime_put_noidle(dev);
	pm_runtime_disable(dev);
	iio_triggered_buffer_cleanup(indio_dev);
	if (mpu3050->irq)
		free_irq(mpu3050->irq, mpu3050);
	iio_device_unregister(indio_dev);
	mpu3050_power_down(mpu3050);

	return 0;
}