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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;
struct mlxsw_sp_port {TYPE_1__ mapping; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct ethtool_eeprom {int dummy; } ;

/* Variables and functions */
 int mlxsw_env_get_module_eeprom (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_eeprom*,int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_get_module_eeprom(struct net_device *netdev,
				      struct ethtool_eeprom *ee,
				      u8 *data)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(netdev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	int err;

	err = mlxsw_env_get_module_eeprom(netdev, mlxsw_sp->core,
					  mlxsw_sp_port->mapping.module, ee,
					  data);

	return err;
}