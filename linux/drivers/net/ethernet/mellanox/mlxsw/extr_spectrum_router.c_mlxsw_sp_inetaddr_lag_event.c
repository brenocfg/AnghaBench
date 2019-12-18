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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_DEFAULT_VID ; 
 int __mlxsw_sp_inetaddr_lag_event (struct net_device*,struct net_device*,unsigned long,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 scalar_t__ netif_is_bridge_port (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_inetaddr_lag_event(struct net_device *lag_dev,
				       unsigned long event,
				       struct netlink_ext_ack *extack)
{
	if (netif_is_bridge_port(lag_dev))
		return 0;

	return __mlxsw_sp_inetaddr_lag_event(lag_dev, lag_dev, event,
					     MLXSW_SP_DEFAULT_VID, extack);
}