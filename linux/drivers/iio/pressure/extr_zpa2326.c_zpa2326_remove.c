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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (struct device const*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  zpa2326_fini_runtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpa2326_power_off (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpa2326_sleep (struct iio_dev*) ; 

void zpa2326_remove(const struct device *parent)
{
	struct iio_dev *indio_dev = dev_get_drvdata(parent);

	iio_device_unregister(indio_dev);
	zpa2326_fini_runtime(indio_dev->dev.parent);
	zpa2326_sleep(indio_dev);
	zpa2326_power_off(indio_dev, iio_priv(indio_dev));
}