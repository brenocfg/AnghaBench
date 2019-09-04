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
struct TYPE_2__ {scalar_t__ qos; scalar_t__ vlan; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  mac; int /*<<< orphan*/  link_state; } ;
struct mlx5_vport {int vport; TYPE_1__ info; } ;
struct mlx5_eswitch {scalar_t__ mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_STATE_OP_MOD_ESW_VPORT ; 
 scalar_t__ SRIOV_LEGACY ; 
 int /*<<< orphan*/  esw_vport_egress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_ingress_config (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  mlx5_modify_nic_vport_mac_address (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_modify_nic_vport_node_guid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_modify_vport_admin_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_esw_vport_cvlan (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void esw_apply_vport_conf(struct mlx5_eswitch *esw,
				 struct mlx5_vport *vport)
{
	int vport_num = vport->vport;

	if (!vport_num)
		return;

	mlx5_modify_vport_admin_state(esw->dev,
				      MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
				      vport_num,
				      vport->info.link_state);
	mlx5_modify_nic_vport_mac_address(esw->dev, vport_num, vport->info.mac);
	mlx5_modify_nic_vport_node_guid(esw->dev, vport_num, vport->info.node_guid);
	modify_esw_vport_cvlan(esw->dev, vport_num, vport->info.vlan, vport->info.qos,
			       (vport->info.vlan || vport->info.qos));

	/* Only legacy mode needs ACLs */
	if (esw->mode == SRIOV_LEGACY) {
		esw_vport_ingress_config(esw, vport);
		esw_vport_egress_config(esw, vport);
	}
}