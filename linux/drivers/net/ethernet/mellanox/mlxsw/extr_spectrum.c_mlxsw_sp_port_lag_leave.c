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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mlxsw_sp_upper {int ref_count; } ;
struct mlxsw_sp_port {scalar_t__ lagged; int /*<<< orphan*/  local_port; int /*<<< orphan*/  default_vlan; int /*<<< orphan*/  lag_id; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_DEFAULT_VID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_core_lag_mapping_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_lag_col_port_remove (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_lag_destroy (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_upper* mlxsw_sp_lag_get (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_lag_uppers_cleanup (struct mlxsw_sp_port*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_pvid_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_flush (struct mlxsw_sp_port*,int) ; 

__attribute__((used)) static void mlxsw_sp_port_lag_leave(struct mlxsw_sp_port *mlxsw_sp_port,
				    struct net_device *lag_dev)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u16 lag_id = mlxsw_sp_port->lag_id;
	struct mlxsw_sp_upper *lag;

	if (!mlxsw_sp_port->lagged)
		return;
	lag = mlxsw_sp_lag_get(mlxsw_sp, lag_id);
	WARN_ON(lag->ref_count == 0);

	mlxsw_sp_lag_col_port_remove(mlxsw_sp_port, lag_id);

	/* Any VLANs configured on the port are no longer valid */
	mlxsw_sp_port_vlan_flush(mlxsw_sp_port, false);
	mlxsw_sp_port_vlan_cleanup(mlxsw_sp_port->default_vlan);
	/* Make the LAG and its directly linked uppers leave bridges they
	 * are memeber in
	 */
	mlxsw_sp_port_lag_uppers_cleanup(mlxsw_sp_port, lag_dev);

	if (lag->ref_count == 1)
		mlxsw_sp_lag_destroy(mlxsw_sp, lag_id);

	mlxsw_core_lag_mapping_clear(mlxsw_sp->core, lag_id,
				     mlxsw_sp_port->local_port);
	mlxsw_sp_port->lagged = 0;
	lag->ref_count--;

	/* Make sure untagged frames are allowed to ingress */
	mlxsw_sp_port_pvid_set(mlxsw_sp_port, MLXSW_SP_DEFAULT_VID);
}