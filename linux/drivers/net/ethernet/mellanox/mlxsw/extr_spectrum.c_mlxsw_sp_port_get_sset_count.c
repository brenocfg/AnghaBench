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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {TYPE_2__* mlxsw_sp; } ;
struct TYPE_4__ {TYPE_1__* ptp_ops; } ;
struct TYPE_3__ {int (* get_stats_count ) () ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int MLXSW_SP_PORT_ETHTOOL_STATS_LEN ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int stub1 () ; 

__attribute__((used)) static int mlxsw_sp_port_get_sset_count(struct net_device *dev, int sset)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		return MLXSW_SP_PORT_ETHTOOL_STATS_LEN +
		       mlxsw_sp_port->mlxsw_sp->ptp_ops->get_stats_count();
	default:
		return -EOPNOTSUPP;
	}
}