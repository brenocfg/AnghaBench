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
struct mlx5e_rep_priv {struct mlx5_flow_handle* vport_rx_rule; struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {TYPE_1__* direct_tir; struct mlx5e_rep_priv* ppriv; TYPE_3__* mdev; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_eswitch_rep {int /*<<< orphan*/  vport; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_5__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_6__ {TYPE_2__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  tirn; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 int PTR_ERR (struct mlx5_flow_handle*) ; 
 struct mlx5_flow_handle* mlx5_eswitch_create_vport_rx_rule (struct mlx5_eswitch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5e_create_direct_rqts (struct mlx5e_priv*) ; 
 int mlx5e_create_direct_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_rqts (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_init_l2_addr (struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5e_init_rep_rx(struct mlx5e_priv *priv)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	struct mlx5_flow_handle *flow_rule;
	int err;

	mlx5e_init_l2_addr(priv);

	err = mlx5e_create_direct_rqts(priv);
	if (err)
		return err;

	err = mlx5e_create_direct_tirs(priv);
	if (err)
		goto err_destroy_direct_rqts;

	flow_rule = mlx5_eswitch_create_vport_rx_rule(esw,
						      rep->vport,
						      priv->direct_tir[0].tirn);
	if (IS_ERR(flow_rule)) {
		err = PTR_ERR(flow_rule);
		goto err_destroy_direct_tirs;
	}
	rpriv->vport_rx_rule = flow_rule;

	return 0;

err_destroy_direct_tirs:
	mlx5e_destroy_direct_tirs(priv);
err_destroy_direct_rqts:
	mlx5e_destroy_direct_rqts(priv);
	return err;
}