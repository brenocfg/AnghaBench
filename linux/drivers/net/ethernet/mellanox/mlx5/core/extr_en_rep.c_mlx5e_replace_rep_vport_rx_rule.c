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
struct mlx5e_rep_priv {struct mlx5_flow_handle* vport_rx_rule; struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {struct mlx5e_rep_priv* ppriv; TYPE_2__* mdev; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_flow_destination {int dummy; } ;
struct mlx5_eswitch_rep {int /*<<< orphan*/  vport; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 int PTR_ERR (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (struct mlx5_flow_handle*) ; 
 struct mlx5_flow_handle* mlx5_eswitch_create_vport_rx_rule (struct mlx5_eswitch*,int /*<<< orphan*/ ,struct mlx5_flow_destination*) ; 

__attribute__((used)) static int mlx5e_replace_rep_vport_rx_rule(struct mlx5e_priv *priv,
					   struct mlx5_flow_destination *dest)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	struct mlx5_flow_handle *flow_rule;

	flow_rule = mlx5_eswitch_create_vport_rx_rule(esw,
						      rep->vport,
						      dest);
	if (IS_ERR(flow_rule))
		return PTR_ERR(flow_rule);

	mlx5_del_flow_rules(rpriv->vport_rx_rule);
	rpriv->vport_rx_rule = flow_rule;
	return 0;
}