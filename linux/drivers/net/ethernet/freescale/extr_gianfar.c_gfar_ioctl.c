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
 int SIOCGHWTSTAMP ; 
 int SIOCSHWTSTAMP ; 
 int gfar_hwtstamp_get (struct net_device*,struct ifreq*) ; 
 int gfar_hwtstamp_set (struct net_device*,struct ifreq*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (struct phy_device*,struct ifreq*,int) ; 

__attribute__((used)) static int gfar_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct phy_device *phydev = dev->phydev;

	if (!netif_running(dev))
		return -EINVAL;

	if (cmd == SIOCSHWTSTAMP)
		return gfar_hwtstamp_set(dev, rq);
	if (cmd == SIOCGHWTSTAMP)
		return gfar_hwtstamp_get(dev, rq);

	if (!phydev)
		return -ENODEV;

	return phy_mii_ioctl(phydev, rq, cmd);
}