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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  mac; int /*<<< orphan*/  link_state; } ;
struct mlx5_vport {scalar_t__ vport; TYPE_1__ info; } ;
struct mlx5_eswitch {scalar_t__ manager_vport; scalar_t__ mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 int /*<<< orphan*/  MLX5_VPORT_STATE_OP_MOD_ESW_VPORT ; 
 int SET_VLAN_INSERT ; 
 int SET_VLAN_STRIP ; 
 int /*<<< orphan*/  esw_vport_egress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_ingress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  mlx5_modify_nic_vport_mac_address (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_modify_nic_vport_node_guid (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_modify_vport_admin_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_esw_vport_cvlan (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void esw_apply_vport_conf(struct mlx5_eswitch *esw,
				 struct mlx5_vport *vport)
{
	u16 vport_num = vport->vport;
	int flags;

	if (esw->manager_vport == vport_num)
		return;

	mlx5_modify_vport_admin_state(esw->dev,
				      MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
				      vport_num, 1,
				      vport->info.link_state);

	/* Host PF has its own mac/guid. */
	if (vport_num) {
		mlx5_modify_nic_vport_mac_address(esw->dev, vport_num,
						  vport->info.mac);
		mlx5_modify_nic_vport_node_guid(esw->dev, vport_num,
						vport->info.node_guid);
	}

	flags = (vport->info.vlan || vport->info.qos) ?
		SET_VLAN_STRIP | SET_VLAN_INSERT : 0;
	modify_esw_vport_cvlan(esw->dev, vport_num, vport->info.vlan, vport->info.qos,
			       flags);

	/* Only legacy mode needs ACLs */
	if (esw->mode == MLX5_ESWITCH_LEGACY) {
		esw_vport_ingress_config(esw, vport);
		esw_vport_egress_config(esw, vport);
	}
}