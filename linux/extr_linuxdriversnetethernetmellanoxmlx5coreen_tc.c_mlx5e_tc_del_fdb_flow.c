#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_tc_flow {int flags; int /*<<< orphan*/ * rule; struct mlx5_esw_flow_attr* esw_attr; } ;
struct mlx5e_priv {TYPE_2__* mdev; } ;
struct mlx5_eswitch {int dummy; } ;
struct mlx5_esw_flow_attr {int action; int /*<<< orphan*/  parse_attr; scalar_t__ mirror_count; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int MLX5E_TC_FLOW_OFFLOADED ; 
 int MLX5_FLOW_CONTEXT_ACTION_ENCAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eswitch_del_offloaded_rule (struct mlx5_eswitch*,int /*<<< orphan*/ ,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  mlx5_eswitch_del_vlan_action (struct mlx5_eswitch*,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  mlx5e_detach_encap (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_detach_mod_hdr (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 

__attribute__((used)) static void mlx5e_tc_del_fdb_flow(struct mlx5e_priv *priv,
				  struct mlx5e_tc_flow *flow)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5_esw_flow_attr *attr = flow->esw_attr;

	if (flow->flags & MLX5E_TC_FLOW_OFFLOADED) {
		flow->flags &= ~MLX5E_TC_FLOW_OFFLOADED;
		if (attr->mirror_count)
			mlx5_eswitch_del_offloaded_rule(esw, flow->rule[1], attr);
		mlx5_eswitch_del_offloaded_rule(esw, flow->rule[0], attr);
	}

	mlx5_eswitch_del_vlan_action(esw, attr);

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_ENCAP) {
		mlx5e_detach_encap(priv, flow);
		kvfree(attr->parse_attr);
	}

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		mlx5e_detach_mod_hdr(priv, flow);
}