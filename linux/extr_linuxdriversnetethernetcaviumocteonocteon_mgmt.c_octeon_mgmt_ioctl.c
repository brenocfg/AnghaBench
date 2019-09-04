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
#define  SIOCSHWTSTAMP 128 
 int octeon_mgmt_ioctl_hwtstamp (struct net_device*,struct ifreq*,int) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ ,struct ifreq*,int) ; 

__attribute__((used)) static int octeon_mgmt_ioctl(struct net_device *netdev,
			     struct ifreq *rq, int cmd)
{
	switch (cmd) {
	case SIOCSHWTSTAMP:
		return octeon_mgmt_ioctl_hwtstamp(netdev, rq, cmd);
	default:
		if (netdev->phydev)
			return phy_mii_ioctl(netdev->phydev, rq, cmd);
		return -EINVAL;
	}
}