#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ethtool_wolinfo {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int phy_ethtool_set_wol (int /*<<< orphan*/ ,struct ethtool_wolinfo*) ; 

__attribute__((used)) static int
mv643xx_eth_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	int err;

	if (!dev->phydev)
		return -EOPNOTSUPP;

	err = phy_ethtool_set_wol(dev->phydev, wol);
	/* Given that mv643xx_eth works without the marvell-specific PHY driver,
	 * this debugging hint is useful to have.
	 */
	if (err == -EOPNOTSUPP)
		netdev_info(dev, "The PHY does not support set_wol, was CONFIG_MARVELL_PHY enabled?\n");
	return err;
}