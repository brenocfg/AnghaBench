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
struct mii_if_info {int phy_id_mask; int reg_num_mask; scalar_t__ phy_id; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct ifreq {int dummy; } ;
struct bcm_enet_priv {scalar_t__ has_phy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  bcm_enet_mdio_read_mii ; 
 int /*<<< orphan*/  bcm_enet_mdio_write_mii ; 
 int generic_mii_ioctl (struct mii_if_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ ,struct ifreq*,int) ; 

__attribute__((used)) static int bcm_enet_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	if (priv->has_phy) {
		if (!dev->phydev)
			return -ENODEV;
		return phy_mii_ioctl(dev->phydev, rq, cmd);
	} else {
		struct mii_if_info mii;

		mii.dev = dev;
		mii.mdio_read = bcm_enet_mdio_read_mii;
		mii.mdio_write = bcm_enet_mdio_write_mii;
		mii.phy_id = 0;
		mii.phy_id_mask = 0x3f;
		mii.reg_num_mask = 0x1f;
		return generic_mii_ioctl(&mii, if_mii(rq), cmd, NULL);
	}
}