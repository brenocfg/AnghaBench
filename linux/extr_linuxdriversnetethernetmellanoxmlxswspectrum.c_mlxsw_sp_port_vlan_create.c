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
typedef  int u16 ;
struct mlxsw_sp_port_vlan {int ref_count; int vid; int /*<<< orphan*/  list; struct mlxsw_sp_port* mlxsw_sp_port; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  vlans_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_port_vlan* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlxsw_sp_port_vlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_port_vlan_set (struct mlxsw_sp_port*,int,int,int,int) ; 

__attribute__((used)) static struct mlxsw_sp_port_vlan *
mlxsw_sp_port_vlan_create(struct mlxsw_sp_port *mlxsw_sp_port, u16 vid)
{
	struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	bool untagged = vid == 1;
	int err;

	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, true, untagged);
	if (err)
		return ERR_PTR(err);

	mlxsw_sp_port_vlan = kzalloc(sizeof(*mlxsw_sp_port_vlan), GFP_KERNEL);
	if (!mlxsw_sp_port_vlan) {
		err = -ENOMEM;
		goto err_port_vlan_alloc;
	}

	mlxsw_sp_port_vlan->mlxsw_sp_port = mlxsw_sp_port;
	mlxsw_sp_port_vlan->ref_count = 1;
	mlxsw_sp_port_vlan->vid = vid;
	list_add(&mlxsw_sp_port_vlan->list, &mlxsw_sp_port->vlans_list);

	return mlxsw_sp_port_vlan;

err_port_vlan_alloc:
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
	return ERR_PTR(err);
}