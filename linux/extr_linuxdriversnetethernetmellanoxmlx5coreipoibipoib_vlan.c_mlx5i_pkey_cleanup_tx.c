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
struct mlx5i_priv {int /*<<< orphan*/  qp; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5i_priv* ppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5i_destroy_underlay_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5i_pkey_cleanup_tx(struct mlx5e_priv *priv)
{
	struct mlx5i_priv *ipriv = priv->ppriv;

	mlx5i_destroy_underlay_qp(priv->mdev, &ipriv->qp);
}