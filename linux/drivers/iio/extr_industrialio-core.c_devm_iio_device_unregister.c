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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_iio_device_match ; 
 int /*<<< orphan*/  devm_iio_device_unreg ; 
 int devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_dev*) ; 

void devm_iio_device_unregister(struct device *dev, struct iio_dev *indio_dev)
{
	int rc;

	rc = devres_release(dev, devm_iio_device_unreg,
			    devm_iio_device_match, indio_dev);
	WARN_ON(rc);
}