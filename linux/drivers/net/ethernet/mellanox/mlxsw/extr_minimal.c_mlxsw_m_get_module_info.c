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
struct mlxsw_m_port {int /*<<< orphan*/  module; TYPE_1__* mlxsw_m; } ;
struct mlxsw_core {int dummy; } ;
struct ethtool_modinfo {int dummy; } ;
struct TYPE_2__ {struct mlxsw_core* core; } ;

/* Variables and functions */
 int mlxsw_env_get_module_info (struct mlxsw_core*,int /*<<< orphan*/ ,struct ethtool_modinfo*) ; 
 struct mlxsw_m_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_m_get_module_info(struct net_device *netdev,
				   struct ethtool_modinfo *modinfo)
{
	struct mlxsw_m_port *mlxsw_m_port = netdev_priv(netdev);
	struct mlxsw_core *core = mlxsw_m_port->mlxsw_m->core;

	return mlxsw_env_get_module_info(core, mlxsw_m_port->module, modinfo);
}