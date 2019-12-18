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
struct phy_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {TYPE_1__ mdiodrv; } ;

/* Variables and functions */
 TYPE_2__ genphy_driver ; 
 int phy_driver_is_genphy_kind (struct phy_device*,int /*<<< orphan*/ *) ; 

bool phy_driver_is_genphy(struct phy_device *phydev)
{
	return phy_driver_is_genphy_kind(phydev,
					 &genphy_driver.mdiodrv.driver);
}