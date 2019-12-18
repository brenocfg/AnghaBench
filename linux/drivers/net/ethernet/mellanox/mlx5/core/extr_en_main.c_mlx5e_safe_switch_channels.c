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
struct mlx5e_priv {int dummy; } ;
struct mlx5e_channels {int dummy; } ;
typedef  int /*<<< orphan*/  mlx5e_fp_hw_modify ;

/* Variables and functions */
 int mlx5e_open_channels (struct mlx5e_priv*,struct mlx5e_channels*) ; 
 int /*<<< orphan*/  mlx5e_switch_priv_channels (struct mlx5e_priv*,struct mlx5e_channels*,int /*<<< orphan*/ ) ; 

int mlx5e_safe_switch_channels(struct mlx5e_priv *priv,
			       struct mlx5e_channels *new_chs,
			       mlx5e_fp_hw_modify hw_modify)
{
	int err;

	err = mlx5e_open_channels(priv, new_chs);
	if (err)
		return err;

	mlx5e_switch_priv_channels(priv, new_chs, hw_modify);
	return 0;
}