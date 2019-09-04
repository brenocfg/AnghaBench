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
 scalar_t__ FDB_UPLINK_VPORT ; 
 int /*<<< orphan*/  MLX5_ESWITCH_MANAGER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mlx5e_is_vf_vport_rep(struct mlx5e_priv *priv)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep;

	if (!MLX5_ESWITCH_MANAGER(priv->mdev))
		return false;

	rep = rpriv->rep;
	if (rep && rep->vport != FDB_UPLINK_VPORT)
		return true;

	return false;
}