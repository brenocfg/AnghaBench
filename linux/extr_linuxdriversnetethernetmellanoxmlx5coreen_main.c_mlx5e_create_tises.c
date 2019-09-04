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
struct mlx5e_priv {int /*<<< orphan*/ * tisn; int /*<<< orphan*/  mdev; TYPE_1__* profile; } ;
struct TYPE_2__ {int max_tc; } ;

/* Variables and functions */
 int mlx5e_create_tis (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_tis (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5e_create_tises(struct mlx5e_priv *priv)
{
	int err;
	int tc;

	for (tc = 0; tc < priv->profile->max_tc; tc++) {
		err = mlx5e_create_tis(priv->mdev, tc, 0, &priv->tisn[tc]);
		if (err)
			goto err_close_tises;
	}

	return 0;

err_close_tises:
	for (tc--; tc >= 0; tc--)
		mlx5e_destroy_tis(priv->mdev, priv->tisn[tc]);

	return err;
}