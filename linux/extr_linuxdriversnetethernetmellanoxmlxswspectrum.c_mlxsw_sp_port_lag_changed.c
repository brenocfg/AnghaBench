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
struct netdev_lag_lower_state_info {int /*<<< orphan*/  tx_enabled; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_port_lag_tx_en_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_port_lag_changed(struct mlxsw_sp_port *mlxsw_sp_port,
				     struct netdev_lag_lower_state_info *info)
{
	return mlxsw_sp_port_lag_tx_en_set(mlxsw_sp_port, info->tx_enabled);
}