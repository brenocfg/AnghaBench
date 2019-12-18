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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {TYPE_1__* ptp_ops; } ;
struct ethtool_ts_info {int dummy; } ;
struct TYPE_2__ {int (* get_ts_info ) (struct mlxsw_sp*,struct ethtool_ts_info*) ;} ;

/* Variables and functions */
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int stub1 (struct mlxsw_sp*,struct ethtool_ts_info*) ; 

__attribute__((used)) static int
mlxsw_sp_get_ts_info(struct net_device *netdev, struct ethtool_ts_info *info)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(netdev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	return mlxsw_sp->ptp_ops->get_ts_info(mlxsw_sp, info);
}