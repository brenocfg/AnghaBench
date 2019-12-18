#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {scalar_t__ gvmi; } ;
struct TYPE_4__ {TYPE_3__ caps; } ;
struct mlx5dr_domain {scalar_t__ type; TYPE_1__ info; struct mlx5dr_domain* peer_dmn; } ;
struct mlx5dr_cmd_vport_cap {int dummy; } ;
struct TYPE_5__ {struct mlx5dr_cmd_vport_cap* caps; struct mlx5dr_domain* dmn; } ;
struct mlx5dr_action {TYPE_2__ vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_ACTION_TYP_VPORT ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_FDB ; 
 struct mlx5dr_action* dr_action_create_generic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*,...) ; 
 struct mlx5dr_cmd_vport_cap* mlx5dr_get_vport_cap (TYPE_3__*,int /*<<< orphan*/ ) ; 

struct mlx5dr_action *
mlx5dr_action_create_dest_vport(struct mlx5dr_domain *dmn,
				u32 vport, u8 vhca_id_valid,
				u16 vhca_id)
{
	struct mlx5dr_cmd_vport_cap *vport_cap;
	struct mlx5dr_domain *vport_dmn;
	struct mlx5dr_action *action;
	u8 peer_vport;

	peer_vport = vhca_id_valid && (vhca_id != dmn->info.caps.gvmi);
	vport_dmn = peer_vport ? dmn->peer_dmn : dmn;
	if (!vport_dmn) {
		mlx5dr_dbg(dmn, "No peer vport domain for given vhca_id\n");
		return NULL;
	}

	if (vport_dmn->type != MLX5DR_DOMAIN_TYPE_FDB) {
		mlx5dr_dbg(dmn, "Domain doesn't support vport actions\n");
		return NULL;
	}

	vport_cap = mlx5dr_get_vport_cap(&vport_dmn->info.caps, vport);
	if (!vport_cap) {
		mlx5dr_dbg(dmn, "Failed to get vport %d caps\n", vport);
		return NULL;
	}

	action = dr_action_create_generic(DR_ACTION_TYP_VPORT);
	if (!action)
		return NULL;

	action->vport.dmn = vport_dmn;
	action->vport.caps = vport_cap;

	return action;
}