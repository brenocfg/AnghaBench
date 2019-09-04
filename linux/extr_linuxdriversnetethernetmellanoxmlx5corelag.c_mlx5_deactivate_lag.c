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
struct mlx5_lag {int /*<<< orphan*/  flags; TYPE_1__* pf; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_LAG_FLAG_BONDED ; 
 int mlx5_cmd_destroy_lag (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 

__attribute__((used)) static void mlx5_deactivate_lag(struct mlx5_lag *ldev)
{
	struct mlx5_core_dev *dev0 = ldev->pf[0].dev;
	int err;

	ldev->flags &= ~MLX5_LAG_FLAG_BONDED;

	err = mlx5_cmd_destroy_lag(dev0);
	if (err)
		mlx5_core_err(dev0,
			      "Failed to destroy LAG (%d)\n",
			      err);
}