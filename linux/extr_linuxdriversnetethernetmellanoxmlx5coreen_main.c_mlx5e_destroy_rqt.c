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
struct mlx5e_rqt {int enabled; int /*<<< orphan*/  rqtn; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_destroy_rqt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5e_destroy_rqt(struct mlx5e_priv *priv, struct mlx5e_rqt *rqt)
{
	rqt->enabled = false;
	mlx5_core_destroy_rqt(priv->mdev, rqt->rqtn);
}