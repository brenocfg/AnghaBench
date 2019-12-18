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
struct mlxsw_sp_port {TYPE_1__* mlxsw_sp; int /*<<< orphan*/  local_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PPLR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pplr_pack (char*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_admin_status_set (struct mlxsw_sp_port*,int) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pplr ; 

__attribute__((used)) static int mlxsw_sp_feature_loopback(struct net_device *dev, bool enable)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	char pplr_pl[MLXSW_REG_PPLR_LEN];
	int err;

	if (netif_running(dev))
		mlxsw_sp_port_admin_status_set(mlxsw_sp_port, false);

	mlxsw_reg_pplr_pack(pplr_pl, mlxsw_sp_port->local_port, enable);
	err = mlxsw_reg_write(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pplr),
			      pplr_pl);

	if (netif_running(dev))
		mlxsw_sp_port_admin_status_set(mlxsw_sp_port, true);

	return err;
}