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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_port_vlan {struct mlxsw_sp_bridge_port* bridge_port; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  pvid; } ;
struct mlxsw_sp_bridge_port {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_port_vlan*) ; 
 int PTR_ERR (struct mlxsw_sp_port_vlan*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_pvid_determine (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_sp_port_pvid_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_vlan_bridge_join (struct mlxsw_sp_port_vlan*,struct mlxsw_sp_bridge_port*,struct netlink_ext_ack*) ; 
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_create (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_destroy (struct mlxsw_sp_port_vlan*) ; 
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_find_by_vid (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_vlan_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
mlxsw_sp_bridge_port_vlan_add(struct mlxsw_sp_port *mlxsw_sp_port,
			      struct mlxsw_sp_bridge_port *bridge_port,
			      u16 vid, bool is_untagged, bool is_pvid,
			      struct netlink_ext_ack *extack)
{
	u16 pvid = mlxsw_sp_port_pvid_determine(mlxsw_sp_port, vid, is_pvid);
	struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	u16 old_pvid = mlxsw_sp_port->pvid;
	int err;

	/* The only valid scenario in which a port-vlan already exists, is if
	 * the VLAN flags were changed and the port-vlan is associated with the
	 * correct bridge port
	 */
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	if (mlxsw_sp_port_vlan &&
	    mlxsw_sp_port_vlan->bridge_port != bridge_port)
		return -EEXIST;

	if (!mlxsw_sp_port_vlan) {
		mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_create(mlxsw_sp_port,
							       vid);
		if (IS_ERR(mlxsw_sp_port_vlan))
			return PTR_ERR(mlxsw_sp_port_vlan);
	}

	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, true,
				     is_untagged);
	if (err)
		goto err_port_vlan_set;

	err = mlxsw_sp_port_pvid_set(mlxsw_sp_port, pvid);
	if (err)
		goto err_port_pvid_set;

	err = mlxsw_sp_port_vlan_bridge_join(mlxsw_sp_port_vlan, bridge_port,
					     extack);
	if (err)
		goto err_port_vlan_bridge_join;

	return 0;

err_port_vlan_bridge_join:
	mlxsw_sp_port_pvid_set(mlxsw_sp_port, old_pvid);
err_port_pvid_set:
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
err_port_vlan_set:
	mlxsw_sp_port_vlan_destroy(mlxsw_sp_port_vlan);
	return err;
}