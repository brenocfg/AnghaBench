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
struct TYPE_3__ {int flags; } ;
struct phy_driver {int (* match_phy_device ) (struct phy_device*) ;int phy_id; int phy_id_mask; TYPE_1__ mdiodrv; } ;
struct TYPE_4__ {int* device_ids; int devices_in_package; } ;
struct phy_device {int phy_id; TYPE_2__ c45_ids; scalar_t__ is_c45; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int MDIO_DEVICE_IS_PHY ; 
 int stub1 (struct phy_device*) ; 
 struct phy_device* to_phy_device (struct device*) ; 
 struct phy_driver* to_phy_driver (struct device_driver*) ; 

__attribute__((used)) static int phy_bus_match(struct device *dev, struct device_driver *drv)
{
	struct phy_device *phydev = to_phy_device(dev);
	struct phy_driver *phydrv = to_phy_driver(drv);
	const int num_ids = ARRAY_SIZE(phydev->c45_ids.device_ids);
	int i;

	if (!(phydrv->mdiodrv.flags & MDIO_DEVICE_IS_PHY))
		return 0;

	if (phydrv->match_phy_device)
		return phydrv->match_phy_device(phydev);

	if (phydev->is_c45) {
		for (i = 1; i < num_ids; i++) {
			if (!(phydev->c45_ids.devices_in_package & (1 << i)))
				continue;

			if ((phydrv->phy_id & phydrv->phy_id_mask) ==
			    (phydev->c45_ids.device_ids[i] &
			     phydrv->phy_id_mask))
				return 1;
		}
		return 0;
	} else {
		return (phydrv->phy_id & phydrv->phy_id_mask) ==
			(phydev->phy_id & phydrv->phy_id_mask);
	}
}