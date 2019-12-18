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

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (struct phy_device*,struct ifreq*,int) ; 

__attribute__((used)) static int ax_ioctl(struct net_device *dev, struct ifreq *req, int cmd)
{
	struct phy_device *phy_dev = dev->phydev;

	if (!netif_running(dev))
		return -EINVAL;

	if (!phy_dev)
		return -ENODEV;

	return phy_mii_ioctl(phy_dev, req, cmd);
}