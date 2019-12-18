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
struct bmp280_data {int /*<<< orphan*/  vddd; int /*<<< orphan*/  vdda; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct bmp280_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

int bmp280_common_remove(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct bmp280_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	pm_runtime_get_sync(data->dev);
	pm_runtime_put_noidle(data->dev);
	pm_runtime_disable(data->dev);
	regulator_disable(data->vdda);
	regulator_disable(data->vddd);
	return 0;
}