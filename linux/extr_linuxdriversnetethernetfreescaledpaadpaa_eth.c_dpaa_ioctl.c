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
 int SIOCGMIIREG ; 
 int SIOCSHWTSTAMP ; 
 int dpaa_ts_ioctl (struct net_device*,struct ifreq*,int) ; 
 int phy_mii_ioctl (scalar_t__,struct ifreq*,int) ; 

__attribute__((used)) static int dpaa_ioctl(struct net_device *net_dev, struct ifreq *rq, int cmd)
{
	int ret = -EINVAL;

	if (cmd == SIOCGMIIREG) {
		if (net_dev->phydev)
			return phy_mii_ioctl(net_dev->phydev, rq, cmd);
	}

	if (cmd == SIOCSHWTSTAMP)
		return dpaa_ts_ioctl(net_dev, rq, cmd);

	return ret;
}