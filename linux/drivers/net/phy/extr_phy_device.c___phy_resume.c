#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_driver {int (* resume ) (struct phy_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct phy_device {int suspended; scalar_t__ drv; int /*<<< orphan*/  lock; TYPE_2__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct phy_device*) ; 
 struct phy_driver* to_phy_driver (int /*<<< orphan*/ ) ; 

int __phy_resume(struct phy_device *phydev)
{
	struct phy_driver *phydrv = to_phy_driver(phydev->mdio.dev.driver);
	int ret = 0;

	WARN_ON(!mutex_is_locked(&phydev->lock));

	if (phydev->drv && phydrv->resume)
		ret = phydrv->resume(phydev);

	if (ret)
		return ret;

	phydev->suspended = false;

	return ret;
}