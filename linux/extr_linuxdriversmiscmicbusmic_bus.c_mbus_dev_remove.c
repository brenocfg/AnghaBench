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
struct mbus_driver {int /*<<< orphan*/  (* remove ) (struct mbus_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct mbus_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mbus_device* dev_to_mbus (struct device*) ; 
 struct mbus_driver* drv_to_mbus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mbus_device*) ; 

__attribute__((used)) static int mbus_dev_remove(struct device *d)
{
	struct mbus_device *dev = dev_to_mbus(d);
	struct mbus_driver *drv = drv_to_mbus(dev->dev.driver);

	drv->remove(dev);
	return 0;
}