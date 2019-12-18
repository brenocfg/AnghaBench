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
struct device {struct device_driver* driver; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {int /*<<< orphan*/  drv; TYPE_1__ mdio; } ;
struct device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static bool phy_driver_is_genphy_kind(struct phy_device *phydev,
				      struct device_driver *driver)
{
	struct device *d = &phydev->mdio.dev;
	bool ret = false;

	if (!phydev->drv)
		return ret;

	get_device(d);
	ret = d->driver == driver;
	put_device(d);

	return ret;
}