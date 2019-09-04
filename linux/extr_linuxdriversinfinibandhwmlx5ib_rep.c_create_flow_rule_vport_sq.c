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
struct TYPE_9__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_10__ {TYPE_4__ mqp; } ;
struct mlx5_ib_sq {struct mlx5_flow_handle* flow_rule; TYPE_5__ base; } ;
struct mlx5_ib_dev {TYPE_3__* rep; TYPE_2__* mdev; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  vport; } ;
struct TYPE_6__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_7__ {TYPE_1__ priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 int PTR_ERR (struct mlx5_flow_handle*) ; 
 struct mlx5_flow_handle* mlx5_eswitch_add_send_to_vport_rule (struct mlx5_eswitch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int create_flow_rule_vport_sq(struct mlx5_ib_dev *dev,
			      struct mlx5_ib_sq *sq)
{
	struct mlx5_flow_handle *flow_rule;
	struct mlx5_eswitch *esw = dev->mdev->priv.eswitch;

	if (!dev->rep)
		return 0;

	flow_rule =
		mlx5_eswitch_add_send_to_vport_rule(esw,
						    dev->rep->vport,
						    sq->base.mqp.qpn);
	if (IS_ERR(flow_rule))
		return PTR_ERR(flow_rule);
	sq->flow_rule = flow_rule;

	return 0;
}