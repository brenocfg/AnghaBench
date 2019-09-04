#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* module_info ) (struct xgbe_prv_data*,struct ethtool_modinfo*) ;} ;
struct TYPE_4__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {TYPE_2__ phy_if; } ;
struct ethtool_modinfo {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int stub1 (struct xgbe_prv_data*,struct ethtool_modinfo*) ; 

__attribute__((used)) static int xgbe_phy_module_info(struct xgbe_prv_data *pdata,
				struct ethtool_modinfo *modinfo)
{
	if (!pdata->phy_if.phy_impl.module_info)
		return -ENXIO;

	return pdata->phy_if.phy_impl.module_info(pdata, modinfo);
}