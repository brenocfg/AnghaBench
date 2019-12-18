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
struct mlx5e_tc_flow {TYPE_3__* priv; } ;
struct mlx5_rep_uplink_priv {int /*<<< orphan*/  unready_flows_lock; } ;
struct mlx5e_rep_priv {struct mlx5_rep_uplink_priv uplink_priv; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_6__ {TYPE_2__* mdev; } ;
struct TYPE_4__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_5__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REP_ETH ; 
 struct mlx5e_rep_priv* mlx5_eswitch_get_uplink_priv (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unready_flow_del (struct mlx5e_tc_flow*) ; 

__attribute__((used)) static void remove_unready_flow(struct mlx5e_tc_flow *flow)
{
	struct mlx5_rep_uplink_priv *uplink_priv;
	struct mlx5e_rep_priv *rpriv;
	struct mlx5_eswitch *esw;

	esw = flow->priv->mdev->priv.eswitch;
	rpriv = mlx5_eswitch_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &rpriv->uplink_priv;

	mutex_lock(&uplink_priv->unready_flows_lock);
	unready_flow_del(flow);
	mutex_unlock(&uplink_priv->unready_flows_lock);
}