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
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SIOCSHWTSTAMP ; 
 int lan743x_ptp_ioctl (struct net_device*,struct ifreq*,int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ ,struct ifreq*,int) ; 

__attribute__((used)) static int lan743x_netdev_ioctl(struct net_device *netdev,
				struct ifreq *ifr, int cmd)
{
	if (!netif_running(netdev))
		return -EINVAL;
	if (cmd == SIOCSHWTSTAMP)
		return lan743x_ptp_ioctl(netdev, ifr, cmd);
	return phy_mii_ioctl(netdev->phydev, ifr, cmd);
}