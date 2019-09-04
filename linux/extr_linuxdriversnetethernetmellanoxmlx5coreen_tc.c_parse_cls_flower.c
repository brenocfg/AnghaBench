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
typedef  scalar_t__ u8 ;
struct tc_cls_flower_offload {int dummy; } ;
struct mlx5e_tc_flow {int flags; TYPE_4__* nic_attr; TYPE_3__* esw_attr; } ;
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; struct mlx5e_rep_priv* ppriv; struct mlx5_core_dev* mdev; } ;
struct mlx5_flow_spec {int dummy; } ;
struct mlx5_eswitch_rep {scalar_t__ vport; } ;
struct TYPE_6__ {scalar_t__ inline_mode; } ;
struct mlx5_eswitch {TYPE_2__ offloads; } ;
struct TYPE_5__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_8__ {scalar_t__ match_level; } ;
struct TYPE_7__ {scalar_t__ match_level; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ FDB_UPLINK_VPORT ; 
 int MLX5E_TC_FLOW_ESWITCH ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 int __parse_cls_flower (struct mlx5e_priv*,struct mlx5_flow_spec*,struct tc_cls_flower_offload*,scalar_t__*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int parse_cls_flower(struct mlx5e_priv *priv,
			    struct mlx5e_tc_flow *flow,
			    struct mlx5_flow_spec *spec,
			    struct tc_cls_flower_offload *f)
{
	struct mlx5_core_dev *dev = priv->mdev;
	struct mlx5_eswitch *esw = dev->priv.eswitch;
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep;
	u8 match_level;
	int err;

	err = __parse_cls_flower(priv, spec, f, &match_level);

	if (!err && (flow->flags & MLX5E_TC_FLOW_ESWITCH)) {
		rep = rpriv->rep;
		if (rep->vport != FDB_UPLINK_VPORT &&
		    (esw->offloads.inline_mode != MLX5_INLINE_MODE_NONE &&
		    esw->offloads.inline_mode < match_level)) {
			netdev_warn(priv->netdev,
				    "Flow is not offloaded due to min inline setting, required %d actual %d\n",
				    match_level, esw->offloads.inline_mode);
			return -EOPNOTSUPP;
		}
	}

	if (flow->flags & MLX5E_TC_FLOW_ESWITCH)
		flow->esw_attr->match_level = match_level;
	else
		flow->nic_attr->match_level = match_level;

	return err;
}