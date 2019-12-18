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
struct umc_driver {int /*<<< orphan*/  (* remove ) (struct umc_dev*) ;} ;
struct umc_dev {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct umc_dev*) ; 
 struct umc_dev* to_umc_dev (struct device*) ; 
 struct umc_driver* to_umc_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int umc_device_remove(struct device *dev)
{
	struct umc_dev *umc;
	struct umc_driver *umc_driver;

	umc_driver = to_umc_driver(dev->driver);
	umc = to_umc_dev(dev);

	umc_driver->remove(umc);
	put_device(dev);
	return 0;
}