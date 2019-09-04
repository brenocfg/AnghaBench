#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_priv {int /*<<< orphan*/ * direct_tir; int /*<<< orphan*/  mdev; TYPE_1__* profile; } ;
struct TYPE_2__ {int (* max_nch ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_tir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

void mlx5e_destroy_direct_tirs(struct mlx5e_priv *priv)
{
	int nch = priv->profile->max_nch(priv->mdev);
	int i;

	for (i = 0; i < nch; i++)
		mlx5e_destroy_tir(priv->mdev, &priv->direct_tir[i]);
}