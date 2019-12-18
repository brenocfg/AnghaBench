#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_tc_flow {struct mlx5_esw_flow_attr* esw_attr; } ;
struct mlx5e_priv {TYPE_2__* mdev; } ;
struct mlx5_eswitch {int dummy; } ;
struct mlx5_esw_flow_attr {int action; int /*<<< orphan*/  counter; int /*<<< orphan*/  counter_dev; TYPE_4__* parse_attr; TYPE_3__* dests; } ;
struct TYPE_8__ {int /*<<< orphan*/ * tun_info; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_5__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_6__ {int /*<<< orphan*/  geneve; TYPE_1__ priv; } ;

/* Variables and functions */
 int MLX5_ESW_DEST_ENCAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_COUNT ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int MLX5_MAX_FLOW_FWD_VPORTS ; 
 int /*<<< orphan*/  NOT_READY ; 
 int /*<<< orphan*/  SLOW ; 
 scalar_t__ flow_flag_test (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (TYPE_4__*) ; 
 int /*<<< orphan*/  mlx5_eswitch_del_vlan_action (struct mlx5_eswitch*,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  mlx5_fc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_flow_has_geneve_opt (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5_geneve_tlv_option_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_detach_encap (struct mlx5e_priv*,struct mlx5e_tc_flow*,int) ; 
 int /*<<< orphan*/  mlx5e_detach_mod_hdr (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 scalar_t__ mlx5e_is_offloaded_flow (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_unoffload_fdb_rules (struct mlx5_eswitch*,struct mlx5e_tc_flow*,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  mlx5e_tc_unoffload_from_slow_path (struct mlx5_eswitch*,struct mlx5e_tc_flow*,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  remove_unready_flow (struct mlx5e_tc_flow*) ; 

__attribute__((used)) static void mlx5e_tc_del_fdb_flow(struct mlx5e_priv *priv,
				  struct mlx5e_tc_flow *flow)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5_esw_flow_attr *attr = flow->esw_attr;
	struct mlx5_esw_flow_attr slow_attr;
	int out_index;

	if (flow_flag_test(flow, NOT_READY)) {
		remove_unready_flow(flow);
		kvfree(attr->parse_attr);
		return;
	}

	if (mlx5e_is_offloaded_flow(flow)) {
		if (flow_flag_test(flow, SLOW))
			mlx5e_tc_unoffload_from_slow_path(esw, flow, &slow_attr);
		else
			mlx5e_tc_unoffload_fdb_rules(esw, flow, attr);
	}

	if (mlx5_flow_has_geneve_opt(flow))
		mlx5_geneve_tlv_option_del(priv->mdev->geneve);

	mlx5_eswitch_del_vlan_action(esw, attr);

	for (out_index = 0; out_index < MLX5_MAX_FLOW_FWD_VPORTS; out_index++)
		if (attr->dests[out_index].flags & MLX5_ESW_DEST_ENCAP) {
			mlx5e_detach_encap(priv, flow, out_index);
			kfree(attr->parse_attr->tun_info[out_index]);
		}
	kvfree(attr->parse_attr);

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		mlx5e_detach_mod_hdr(priv, flow);

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_COUNT)
		mlx5_fc_destroy(attr->counter_dev, attr->counter);
}