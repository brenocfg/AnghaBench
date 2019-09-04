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
struct tc_cls_flower_offload {int /*<<< orphan*/  exts; int /*<<< orphan*/  cookie; } ;
struct rhashtable {int dummy; } ;
struct mlx5e_tc_flow_parse_attr {int /*<<< orphan*/  spec; } ;
struct mlx5e_tc_flow {int flags; int /*<<< orphan*/  node; TYPE_3__* esw_attr; int /*<<< orphan*/ * rule; struct mlx5e_priv* priv; int /*<<< orphan*/  cookie; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; TYPE_2__* mdev; } ;
struct mlx5_nic_flow_attr {int dummy; } ;
struct mlx5_eswitch {scalar_t__ mode; } ;
struct mlx5_esw_flow_attr {int dummy; } ;
struct TYPE_6__ {int action; } ;
struct TYPE_4__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_5__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MLX5E_TC_FLOW_ESWITCH ; 
 int MLX5E_TC_FLOW_NIC ; 
 int MLX5E_TC_FLOW_OFFLOADED ; 
 int MLX5_FLOW_CONTEXT_ACTION_ENCAP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SRIOV_OFFLOADS ; 
 int /*<<< orphan*/  get_flags (int,int*) ; 
 struct rhashtable* get_tc_ht (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  kvfree (struct mlx5e_tc_flow_parse_attr*) ; 
 struct mlx5e_tc_flow_parse_attr* kvzalloc (int,int /*<<< orphan*/ ) ; 
 struct mlx5e_tc_flow* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_tc_add_fdb_flow (struct mlx5e_priv*,struct mlx5e_tc_flow_parse_attr*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_add_nic_flow (struct mlx5e_priv*,struct mlx5e_tc_flow_parse_attr*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_del_flow (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  netdev_warn_once (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int parse_cls_flower (struct mlx5e_priv*,struct mlx5e_tc_flow*,int /*<<< orphan*/ *,struct tc_cls_flower_offload*) ; 
 int parse_tc_fdb_actions (struct mlx5e_priv*,int /*<<< orphan*/ ,struct mlx5e_tc_flow_parse_attr*,struct mlx5e_tc_flow*) ; 
 int parse_tc_nic_actions (struct mlx5e_priv*,int /*<<< orphan*/ ,struct mlx5e_tc_flow_parse_attr*,struct mlx5e_tc_flow*) ; 
 int rhashtable_insert_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5e_tc_flow* rhashtable_lookup_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_ht_params ; 

int mlx5e_configure_flower(struct mlx5e_priv *priv,
			   struct tc_cls_flower_offload *f, int flags)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5e_tc_flow_parse_attr *parse_attr;
	struct rhashtable *tc_ht = get_tc_ht(priv);
	struct mlx5e_tc_flow *flow;
	int attr_size, err = 0;
	u8 flow_flags = 0;

	get_flags(flags, &flow_flags);

	flow = rhashtable_lookup_fast(tc_ht, &f->cookie, tc_ht_params);
	if (flow) {
		netdev_warn_once(priv->netdev, "flow cookie %lx already exists, ignoring\n", f->cookie);
		return 0;
	}

	if (esw && esw->mode == SRIOV_OFFLOADS) {
		flow_flags |= MLX5E_TC_FLOW_ESWITCH;
		attr_size  = sizeof(struct mlx5_esw_flow_attr);
	} else {
		flow_flags |= MLX5E_TC_FLOW_NIC;
		attr_size  = sizeof(struct mlx5_nic_flow_attr);
	}

	flow = kzalloc(sizeof(*flow) + attr_size, GFP_KERNEL);
	parse_attr = kvzalloc(sizeof(*parse_attr), GFP_KERNEL);
	if (!parse_attr || !flow) {
		err = -ENOMEM;
		goto err_free;
	}

	flow->cookie = f->cookie;
	flow->flags = flow_flags;
	flow->priv = priv;

	err = parse_cls_flower(priv, flow, &parse_attr->spec, f);
	if (err < 0)
		goto err_free;

	if (flow->flags & MLX5E_TC_FLOW_ESWITCH) {
		err = parse_tc_fdb_actions(priv, f->exts, parse_attr, flow);
		if (err < 0)
			goto err_free;
		flow->rule[0] = mlx5e_tc_add_fdb_flow(priv, parse_attr, flow);
	} else {
		err = parse_tc_nic_actions(priv, f->exts, parse_attr, flow);
		if (err < 0)
			goto err_free;
		flow->rule[0] = mlx5e_tc_add_nic_flow(priv, parse_attr, flow);
	}

	if (IS_ERR(flow->rule[0])) {
		err = PTR_ERR(flow->rule[0]);
		if (err != -EAGAIN)
			goto err_free;
	}

	if (err != -EAGAIN)
		flow->flags |= MLX5E_TC_FLOW_OFFLOADED;

	if (!(flow->flags & MLX5E_TC_FLOW_ESWITCH) ||
	    !(flow->esw_attr->action & MLX5_FLOW_CONTEXT_ACTION_ENCAP))
		kvfree(parse_attr);

	err = rhashtable_insert_fast(tc_ht, &flow->node, tc_ht_params);
	if (err) {
		mlx5e_tc_del_flow(priv, flow);
		kfree(flow);
	}

	return err;

err_free:
	kvfree(parse_attr);
	kfree(flow);
	return err;
}