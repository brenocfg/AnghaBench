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
struct net_device {TYPE_1__* phydev; } ;
struct TYPE_2__ {scalar_t__ autoneg; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int phy_start_aneg (TYPE_1__*) ; 

__attribute__((used)) static int dpaa_nway_reset(struct net_device *net_dev)
{
	int err;

	if (!net_dev->phydev) {
		netdev_err(net_dev, "phy device not initialized\n");
		return -ENODEV;
	}

	err = 0;
	if (net_dev->phydev->autoneg) {
		err = phy_start_aneg(net_dev->phydev);
		if (err < 0)
			netdev_err(net_dev, "phy_start_aneg() = %d\n",
				   err);
	}

	return err;
}