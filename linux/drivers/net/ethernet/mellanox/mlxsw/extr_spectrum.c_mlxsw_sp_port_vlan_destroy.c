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
struct mlxsw_sp_port_vlan {int /*<<< orphan*/  list; int /*<<< orphan*/  vid; struct mlxsw_sp_port* mlxsw_sp_port; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_port_vlan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_cleanup (struct mlxsw_sp_port_vlan*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void mlxsw_sp_port_vlan_destroy(struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
{
	struct mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	u16 vid = mlxsw_sp_port_vlan->vid;

	mlxsw_sp_port_vlan_cleanup(mlxsw_sp_port_vlan);
	list_del(&mlxsw_sp_port_vlan->list);
	kfree(mlxsw_sp_port_vlan);
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
}