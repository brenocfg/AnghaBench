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
struct phy_device {scalar_t__ is_c45; TYPE_1__* drv; } ;
struct TYPE_2__ {int (* aneg_done ) (struct phy_device*) ;} ;

/* Variables and functions */
 int genphy_aneg_done (struct phy_device*) ; 
 int genphy_c45_aneg_done (struct phy_device*) ; 
 int stub1 (struct phy_device*) ; 

int phy_aneg_done(struct phy_device *phydev)
{
	if (phydev->drv && phydev->drv->aneg_done)
		return phydev->drv->aneg_done(phydev);
	else if (phydev->is_c45)
		return genphy_c45_aneg_done(phydev);
	else
		return genphy_aneg_done(phydev);
}