#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int pfc_mode_enable; TYPE_1__* tc_config; } ;
struct TYPE_8__ {TYPE_3__* tc_config; } ;
struct ixgbe_adapter {TYPE_2__ temp_dcb_cfg; TYPE_4__ dcb_cfg; } ;
struct TYPE_7__ {scalar_t__ dcb_pfc; } ;
struct TYPE_5__ {scalar_t__ dcb_pfc; } ;

/* Variables and functions */
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbe_dcbnl_set_pfc_cfg(struct net_device *netdev, int priority,
				    u8 setting)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	adapter->temp_dcb_cfg.tc_config[priority].dcb_pfc = setting;
	if (adapter->temp_dcb_cfg.tc_config[priority].dcb_pfc !=
	    adapter->dcb_cfg.tc_config[priority].dcb_pfc)
		adapter->temp_dcb_cfg.pfc_mode_enable = true;
}