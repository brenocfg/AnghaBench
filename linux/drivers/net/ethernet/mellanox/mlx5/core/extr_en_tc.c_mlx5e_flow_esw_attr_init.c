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
struct mlx5e_tc_flow_parse_attr {int dummy; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_eswitch_rep {int dummy; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct mlx5_esw_flow_attr {struct mlx5_core_dev* counter_dev; struct mlx5_core_dev* in_mdev; struct mlx5_eswitch_rep* in_rep; int /*<<< orphan*/  prio; int /*<<< orphan*/  chain; struct mlx5e_tc_flow_parse_attr* parse_attr; } ;
struct TYPE_4__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  prio; int /*<<< orphan*/  chain_index; } ;
struct flow_cls_offload {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_ESW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_COUNTER_SOURCE_ESWITCH ; 
 int /*<<< orphan*/  counter_eswitch_affinity ; 

__attribute__((used)) static void
mlx5e_flow_esw_attr_init(struct mlx5_esw_flow_attr *esw_attr,
			 struct mlx5e_priv *priv,
			 struct mlx5e_tc_flow_parse_attr *parse_attr,
			 struct flow_cls_offload *f,
			 struct mlx5_eswitch_rep *in_rep,
			 struct mlx5_core_dev *in_mdev)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;

	esw_attr->parse_attr = parse_attr;
	esw_attr->chain = f->common.chain_index;
	esw_attr->prio = f->common.prio;

	esw_attr->in_rep = in_rep;
	esw_attr->in_mdev = in_mdev;

	if (MLX5_CAP_ESW(esw->dev, counter_eswitch_affinity) ==
	    MLX5_COUNTER_SOURCE_ESWITCH)
		esw_attr->counter_dev = in_mdev;
	else
		esw_attr->counter_dev = priv->mdev;
}