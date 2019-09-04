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
struct mlxsw_sp_bridge_port {int lagged; int /*<<< orphan*/  system_port; int /*<<< orphan*/  lag_id; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SFDF_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sfdf_fid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfdf_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfdf_port_fid_system_port_set (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_fdb_flush_type (int) ; 
 int /*<<< orphan*/  sfdf ; 

__attribute__((used)) static int
mlxsw_sp_bridge_port_fdb_flush(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_bridge_port *bridge_port,
			       u16 fid_index)
{
	bool lagged = bridge_port->lagged;
	char sfdf_pl[MLXSW_REG_SFDF_LEN];
	u16 system_port;

	system_port = lagged ? bridge_port->lag_id : bridge_port->system_port;
	mlxsw_reg_sfdf_pack(sfdf_pl, mlxsw_sp_fdb_flush_type(lagged));
	mlxsw_reg_sfdf_fid_set(sfdf_pl, fid_index);
	mlxsw_reg_sfdf_port_fid_system_port_set(sfdf_pl, system_port);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sfdf), sfdf_pl);
}