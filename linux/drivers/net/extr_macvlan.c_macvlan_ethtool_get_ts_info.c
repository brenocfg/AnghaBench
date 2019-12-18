#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy_device {TYPE_1__* drv; } ;
struct net_device {struct phy_device* phydev; struct ethtool_ops* ethtool_ops; } ;
struct ethtool_ts_info {int so_timestamping; int phc_index; } ;
struct ethtool_ops {int (* get_ts_info ) (struct net_device*,struct ethtool_ts_info*) ;} ;
struct TYPE_2__ {int (* ts_info ) (struct phy_device*,struct ethtool_ts_info*) ;} ;

/* Variables and functions */
 int SOF_TIMESTAMPING_RX_SOFTWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 struct net_device* macvlan_dev_real_dev (struct net_device*) ; 
 int stub1 (struct phy_device*,struct ethtool_ts_info*) ; 
 int stub2 (struct net_device*,struct ethtool_ts_info*) ; 

__attribute__((used)) static int macvlan_ethtool_get_ts_info(struct net_device *dev,
				       struct ethtool_ts_info *info)
{
	struct net_device *real_dev = macvlan_dev_real_dev(dev);
	const struct ethtool_ops *ops = real_dev->ethtool_ops;
	struct phy_device *phydev = real_dev->phydev;

	if (phydev && phydev->drv && phydev->drv->ts_info) {
		 return phydev->drv->ts_info(phydev, info);
	} else if (ops->get_ts_info) {
		return ops->get_ts_info(real_dev, info);
	} else {
		info->so_timestamping = SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		info->phc_index = -1;
	}

	return 0;
}