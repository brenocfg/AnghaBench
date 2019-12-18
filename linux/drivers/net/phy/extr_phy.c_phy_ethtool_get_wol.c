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
struct phy_device {TYPE_1__* drv; } ;
struct ethtool_wolinfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_wol ) (struct phy_device*,struct ethtool_wolinfo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct phy_device*,struct ethtool_wolinfo*) ; 

void phy_ethtool_get_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	if (phydev->drv && phydev->drv->get_wol)
		phydev->drv->get_wol(phydev, wol);
}