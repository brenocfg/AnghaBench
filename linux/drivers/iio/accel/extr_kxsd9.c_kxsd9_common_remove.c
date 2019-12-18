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
struct kxsd9_state {int dummy; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct kxsd9_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  kxsd9_power_down (struct kxsd9_state*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 

int kxsd9_common_remove(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct kxsd9_state *st = iio_priv(indio_dev);

	iio_triggered_buffer_cleanup(indio_dev);
	iio_device_unregister(indio_dev);
	pm_runtime_get_sync(dev);
	pm_runtime_put_noidle(dev);
	pm_runtime_disable(dev);
	kxsd9_power_down(st);

	return 0;
}