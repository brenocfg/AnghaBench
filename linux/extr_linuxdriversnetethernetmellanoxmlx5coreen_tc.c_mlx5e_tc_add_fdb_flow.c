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
struct net_device {int dummy; } ;
struct mlx5e_tc_flow_parse_attr {int /*<<< orphan*/  spec; int /*<<< orphan*/  mod_hdr_actions; int /*<<< orphan*/  tun_info; } ;
struct mlx5e_tc_flow {struct mlx5_flow_handle** rule; struct mlx5_esw_flow_attr* esw_attr; } ;
struct mlx5e_rep_priv {int /*<<< orphan*/  rep; } ;
struct mlx5e_priv {TYPE_3__* mdev; struct mlx5e_rep_priv* ppriv; int /*<<< orphan*/  netdev; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;
struct mlx5_esw_flow_attr {int action; size_t out_count; scalar_t__ mirror_count; TYPE_3__** out_mdev; int /*<<< orphan*/ * out_rep; TYPE_2__* parse_attr; } ;
struct TYPE_4__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_6__ {TYPE_1__ priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  mirred_ifindex; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct mlx5_flow_handle* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 int MLX5_FLOW_CONTEXT_ACTION_ENCAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct mlx5_flow_handle* mlx5_eswitch_add_fwd_rule (struct mlx5_eswitch*,int /*<<< orphan*/ *,struct mlx5_esw_flow_attr*) ; 
 struct mlx5_flow_handle* mlx5_eswitch_add_offloaded_rule (struct mlx5_eswitch*,int /*<<< orphan*/ *,struct mlx5_esw_flow_attr*) ; 
 int mlx5_eswitch_add_vlan_action (struct mlx5_eswitch*,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  mlx5_eswitch_del_offloaded_rule (struct mlx5_eswitch*,struct mlx5_flow_handle*,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  mlx5_eswitch_del_vlan_action (struct mlx5_eswitch*,struct mlx5_esw_flow_attr*) ; 
 int mlx5e_attach_encap (struct mlx5e_priv*,int /*<<< orphan*/ *,struct net_device*,struct net_device**,struct mlx5e_tc_flow*) ; 
 int mlx5e_attach_mod_hdr (struct mlx5e_priv*,struct mlx5e_tc_flow*,struct mlx5e_tc_flow_parse_attr*) ; 
 int /*<<< orphan*/  mlx5e_detach_encap (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_detach_mod_hdr (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct mlx5_flow_handle *
mlx5e_tc_add_fdb_flow(struct mlx5e_priv *priv,
		      struct mlx5e_tc_flow_parse_attr *parse_attr,
		      struct mlx5e_tc_flow *flow)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5_esw_flow_attr *attr = flow->esw_attr;
	struct net_device *out_dev, *encap_dev = NULL;
	struct mlx5_flow_handle *rule = NULL;
	struct mlx5e_rep_priv *rpriv;
	struct mlx5e_priv *out_priv;
	int err;

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_ENCAP) {
		out_dev = __dev_get_by_index(dev_net(priv->netdev),
					     attr->parse_attr->mirred_ifindex);
		err = mlx5e_attach_encap(priv, &parse_attr->tun_info,
					 out_dev, &encap_dev, flow);
		if (err) {
			rule = ERR_PTR(err);
			if (err != -EAGAIN)
				goto err_attach_encap;
		}
		out_priv = netdev_priv(encap_dev);
		rpriv = out_priv->ppriv;
		attr->out_rep[attr->out_count] = rpriv->rep;
		attr->out_mdev[attr->out_count++] = out_priv->mdev;
	}

	err = mlx5_eswitch_add_vlan_action(esw, attr);
	if (err) {
		rule = ERR_PTR(err);
		goto err_add_vlan;
	}

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR) {
		err = mlx5e_attach_mod_hdr(priv, flow, parse_attr);
		kfree(parse_attr->mod_hdr_actions);
		if (err) {
			rule = ERR_PTR(err);
			goto err_mod_hdr;
		}
	}

	/* we get here if (1) there's no error (rule being null) or when
	 * (2) there's an encap action and we're on -EAGAIN (no valid neigh)
	 */
	if (rule != ERR_PTR(-EAGAIN)) {
		rule = mlx5_eswitch_add_offloaded_rule(esw, &parse_attr->spec, attr);
		if (IS_ERR(rule))
			goto err_add_rule;

		if (attr->mirror_count) {
			flow->rule[1] = mlx5_eswitch_add_fwd_rule(esw, &parse_attr->spec, attr);
			if (IS_ERR(flow->rule[1]))
				goto err_fwd_rule;
		}
	}
	return rule;

err_fwd_rule:
	mlx5_eswitch_del_offloaded_rule(esw, rule, attr);
	rule = flow->rule[1];
err_add_rule:
	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		mlx5e_detach_mod_hdr(priv, flow);
err_mod_hdr:
	mlx5_eswitch_del_vlan_action(esw, attr);
err_add_vlan:
	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_ENCAP)
		mlx5e_detach_encap(priv, flow);
err_attach_encap:
	return rule;
}