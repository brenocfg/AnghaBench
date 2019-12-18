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
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp_bridge_port {int dummy; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_DEFAULT_VID ; 
 int /*<<< orphan*/  mlxsw_sp_port_pvid_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_bridge_8021q_port_leave(struct mlxsw_sp_bridge_device *bridge_device,
				 struct mlxsw_sp_bridge_port *bridge_port,
				 struct mlxsw_sp_port *mlxsw_sp_port)
{
	/* Make sure untagged frames are allowed to ingress */
	mlxsw_sp_port_pvid_set(mlxsw_sp_port, MLXSW_SP_DEFAULT_VID);
}