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
struct umc_driver {int (* probe ) (struct umc_dev*) ;} ;
struct umc_dev {int dummy; } ;
struct device {int /*<<< orphan*/  parent; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int stub1 (struct umc_dev*) ; 
 struct umc_dev* to_umc_dev (struct device*) ; 
 struct umc_driver* to_umc_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umc_bus_rescan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int umc_device_probe(struct device *dev)
{
	struct umc_dev *umc;
	struct umc_driver *umc_driver;
	int err;

	umc_driver = to_umc_driver(dev->driver);
	umc = to_umc_dev(dev);

	get_device(dev);
	err = umc_driver->probe(umc);
	if (err)
		put_device(dev);
	else
		umc_bus_rescan(dev->parent);

	return err;
}