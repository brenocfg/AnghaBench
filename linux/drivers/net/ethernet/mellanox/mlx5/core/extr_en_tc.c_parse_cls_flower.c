#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_tc_flow {TYPE_5__* nic_attr; TYPE_4__* esw_attr; } ;
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; struct mlx5e_rep_priv* ppriv; struct mlx5_core_dev* mdev; } ;
struct mlx5_flow_spec {int dummy; } ;
struct mlx5_eswitch_rep {scalar_t__ vport; } ;
struct TYPE_8__ {scalar_t__ inline_mode; } ;
struct mlx5_eswitch {TYPE_3__ offloads; } ;
struct TYPE_7__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_6__ {struct netlink_ext_ack* extack; } ;
struct flow_cls_offload {TYPE_1__ common; } ;
struct TYPE_10__ {scalar_t__ match_level; } ;
struct TYPE_9__ {scalar_t__ outer_match_level; scalar_t__ inner_match_level; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 scalar_t__ MLX5_MATCH_NONE ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int __parse_cls_flower (struct mlx5e_priv*,struct mlx5_flow_spec*,struct flow_cls_offload*,struct net_device*,scalar_t__*,scalar_t__*) ; 
 int mlx5e_is_eswitch_flow (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int parse_cls_flower(struct mlx5e_priv *priv,
			    struct mlx5e_tc_flow *flow,
			    struct mlx5_flow_spec *spec,
			    struct flow_cls_offload *f,
			    struct net_device *filter_dev)
{
	u8 inner_match_level, outer_match_level, non_tunnel_match_level;
	struct netlink_ext_ack *extack = f->common.extack;
	struct mlx5_core_dev *dev = priv->mdev;
	struct mlx5_eswitch *esw = dev->priv.eswitch;
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep;
	bool is_eswitch_flow;
	int err;

	inner_match_level = MLX5_MATCH_NONE;
	outer_match_level = MLX5_MATCH_NONE;

	err = __parse_cls_flower(priv, spec, f, filter_dev, &inner_match_level,
				 &outer_match_level);
	non_tunnel_match_level = (inner_match_level == MLX5_MATCH_NONE) ?
				 outer_match_level : inner_match_level;

	is_eswitch_flow = mlx5e_is_eswitch_flow(flow);
	if (!err && is_eswitch_flow) {
		rep = rpriv->rep;
		if (rep->vport != MLX5_VPORT_UPLINK &&
		    (esw->offloads.inline_mode != MLX5_INLINE_MODE_NONE &&
		    esw->offloads.inline_mode < non_tunnel_match_level)) {
			NL_SET_ERR_MSG_MOD(extack,
					   "Flow is not offloaded due to min inline setting");
			netdev_warn(priv->netdev,
				    "Flow is not offloaded due to min inline setting, required %d actual %d\n",
				    non_tunnel_match_level, esw->offloads.inline_mode);
			return -EOPNOTSUPP;
		}
	}

	if (is_eswitch_flow) {
		flow->esw_attr->inner_match_level = inner_match_level;
		flow->esw_attr->outer_match_level = outer_match_level;
	} else {
		flow->nic_attr->match_level = non_tunnel_match_level;
	}

	return err;
}