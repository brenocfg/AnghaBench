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
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {TYPE_2__* mdev; struct mlx5e_rep_priv* ppriv; } ;
struct mlx5_eswitch_rep {scalar_t__ vport; } ;
struct mlx5_eswitch {scalar_t__ mode; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 scalar_t__ FDB_UPLINK_VPORT ; 
 int /*<<< orphan*/  MLX5_ESWITCH_MANAGER (TYPE_2__*) ; 
 scalar_t__ SRIOV_OFFLOADS ; 

bool mlx5e_is_uplink_rep(struct mlx5e_priv *priv)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep;

	if (!MLX5_ESWITCH_MANAGER(priv->mdev))
		return false;

	rep = rpriv->rep;
	if (esw->mode == SRIOV_OFFLOADS &&
	    rep && rep->vport == FDB_UPLINK_VPORT)
		return true;

	return false;
}