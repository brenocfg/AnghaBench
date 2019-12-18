#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5e_rep_priv* ppriv; } ;
struct mlx5_eswitch_rep {scalar_t__ vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_ESWITCH_MANAGER (int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 

bool mlx5e_is_uplink_rep(struct mlx5e_priv *priv)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep;

	if (!MLX5_ESWITCH_MANAGER(priv->mdev))
		return false;

	if (!rpriv) /* non vport rep mlx5e instances don't use this field */
		return false;

	rep = rpriv->rep;
	return (rep->vport == MLX5_VPORT_UPLINK);
}