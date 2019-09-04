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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct ifreq {int dummy; } ;
struct fec_enet_private {scalar_t__ bufdesc_ex; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int SIOCGHWTSTAMP ; 
 int SIOCSHWTSTAMP ; 
 int fec_ptp_get (struct net_device*,struct ifreq*) ; 
 int fec_ptp_set (struct net_device*,struct ifreq*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (struct phy_device*,struct ifreq*,int) ; 

__attribute__((used)) static int fec_enet_ioctl(struct net_device *ndev, struct ifreq *rq, int cmd)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;

	if (!netif_running(ndev))
		return -EINVAL;

	if (!phydev)
		return -ENODEV;

	if (fep->bufdesc_ex) {
		if (cmd == SIOCSHWTSTAMP)
			return fec_ptp_set(ndev, rq);
		if (cmd == SIOCGHWTSTAMP)
			return fec_ptp_get(ndev, rq);
	}

	return phy_mii_ioctl(phydev, rq, cmd);
}