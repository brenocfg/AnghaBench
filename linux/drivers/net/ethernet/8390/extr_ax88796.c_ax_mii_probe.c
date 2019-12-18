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
struct phy_device {int /*<<< orphan*/  irq; TYPE_1__* drv; } ;
struct net_device {int dummy; } ;
struct ax_device {int /*<<< orphan*/  mii_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  ax_handle_link_change ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static int ax_mii_probe(struct net_device *dev)
{
	struct ax_device  *ax = to_ax_dev(dev);
	struct phy_device *phy_dev = NULL;
	int ret;

	/* find the first phy */
	phy_dev = phy_find_first(ax->mii_bus);
	if (!phy_dev) {
		netdev_err(dev, "no PHY found\n");
		return -ENODEV;
	}

	ret = phy_connect_direct(dev, phy_dev, ax_handle_link_change,
				 PHY_INTERFACE_MODE_MII);
	if (ret) {
		netdev_err(dev, "Could not attach to PHY\n");
		return ret;
	}

	phy_set_max_speed(phy_dev, SPEED_100);

	netdev_info(dev, "PHY driver [%s] (mii_bus:phy_addr=%s, irq=%d)\n",
		    phy_dev->drv->name, phydev_name(phy_dev), phy_dev->irq);

	return 0;
}