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
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; } ;
struct ifreq {int dummy; } ;
struct ef4_nic {int /*<<< orphan*/  mdio; } ;

/* Variables and functions */
 int MDIO_PHY_ID_C45 ; 
 int SIOCGMIIREG ; 
 int SIOCSMIIREG ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int mdio_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ef4_ioctl(struct net_device *net_dev, struct ifreq *ifr, int cmd)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	struct mii_ioctl_data *data = if_mii(ifr);

	/* Convert phy_id from older PRTAD/DEVAD format */
	if ((cmd == SIOCGMIIREG || cmd == SIOCSMIIREG) &&
	    (data->phy_id & 0xfc00) == 0x0400)
		data->phy_id ^= MDIO_PHY_ID_C45 | 0x0400;

	return mdio_mii_ioctl(&efx->mdio, data, cmd);
}