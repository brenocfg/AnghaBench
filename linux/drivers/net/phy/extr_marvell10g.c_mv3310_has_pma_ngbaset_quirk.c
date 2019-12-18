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
struct TYPE_2__ {int devices_in_package; int* device_ids; } ;
struct phy_device {TYPE_1__ c45_ids; } ;

/* Variables and functions */
 int MDIO_DEVS_PMAPMD ; 
 size_t MDIO_MMD_PMAPMD ; 
 int MV_PHY_ALASKA_NBT_QUIRK_MASK ; 
 int MV_PHY_ALASKA_NBT_QUIRK_REV ; 

__attribute__((used)) static bool mv3310_has_pma_ngbaset_quirk(struct phy_device *phydev)
{
	if (!(phydev->c45_ids.devices_in_package & MDIO_DEVS_PMAPMD))
		return false;

	/* Only some revisions of the 88X3310 family PMA seem to be impacted */
	return (phydev->c45_ids.device_ids[MDIO_MMD_PMAPMD] &
		MV_PHY_ALASKA_NBT_QUIRK_MASK) == MV_PHY_ALASKA_NBT_QUIRK_REV;
}