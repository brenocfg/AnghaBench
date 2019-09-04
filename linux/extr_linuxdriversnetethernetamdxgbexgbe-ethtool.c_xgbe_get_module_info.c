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
struct TYPE_2__ {int (* module_info ) (struct xgbe_prv_data*,struct ethtool_modinfo*) ;} ;
struct xgbe_prv_data {TYPE_1__ phy_if; } ;
struct net_device {int dummy; } ;
struct ethtool_modinfo {int dummy; } ;

/* Variables and functions */
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int stub1 (struct xgbe_prv_data*,struct ethtool_modinfo*) ; 

__attribute__((used)) static int xgbe_get_module_info(struct net_device *netdev,
				struct ethtool_modinfo *modinfo)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	return pdata->phy_if.module_info(pdata, modinfo);
}