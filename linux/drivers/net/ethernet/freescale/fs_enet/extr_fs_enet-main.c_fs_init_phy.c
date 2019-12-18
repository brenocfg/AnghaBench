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
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct fs_enet_private {int oldduplex; TYPE_1__* fpi; scalar_t__ oldspeed; scalar_t__ oldlink; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;
struct TYPE_2__ {int /*<<< orphan*/  phy_node; scalar_t__ use_rmii; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RMII ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fs_adjust_link ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fs_init_phy(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);
	struct phy_device *phydev;
	phy_interface_t iface;

	fep->oldlink = 0;
	fep->oldspeed = 0;
	fep->oldduplex = -1;

	iface = fep->fpi->use_rmii ?
		PHY_INTERFACE_MODE_RMII : PHY_INTERFACE_MODE_MII;

	phydev = of_phy_connect(dev, fep->fpi->phy_node, &fs_adjust_link, 0,
				iface);
	if (!phydev) {
		dev_err(&dev->dev, "Could not attach to PHY\n");
		return -ENODEV;
	}

	return 0;
}