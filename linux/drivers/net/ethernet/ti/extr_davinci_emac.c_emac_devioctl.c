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
struct net_device {scalar_t__ phydev; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (scalar_t__,struct ifreq*,int) ; 

__attribute__((used)) static int emac_devioctl(struct net_device *ndev, struct ifreq *ifrq, int cmd)
{
	if (!(netif_running(ndev)))
		return -EINVAL;

	/* TODO: Add phy read and write and private statistics get feature */

	if (ndev->phydev)
		return phy_mii_ioctl(ndev->phydev, ifrq, cmd);
	else
		return -EOPNOTSUPP;
}