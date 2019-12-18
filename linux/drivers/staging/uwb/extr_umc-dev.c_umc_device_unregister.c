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
struct umc_dev {int /*<<< orphan*/  resource; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 struct device* get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 

void umc_device_unregister(struct umc_dev *umc)
{
	struct device *dev;
	if (!umc)
		return;
	dev = get_device(&umc->dev);
	device_unregister(&umc->dev);
	release_resource(&umc->resource);
	put_device(dev);
}