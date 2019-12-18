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
typedef  int u8 ;
struct mlx5_lag {int flags; TYPE_1__* pf; } ;
struct mlx5_core_dev {int dummy; } ;
struct lag_tracker {int dummy; } ;
struct TYPE_2__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int MLX5_LAG_FLAG_ROCE ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int mlx5_create_lag (struct mlx5_lag*,struct lag_tracker*) ; 

int mlx5_activate_lag(struct mlx5_lag *ldev,
		      struct lag_tracker *tracker,
		      u8 flags)
{
	bool roce_lag = !!(flags & MLX5_LAG_FLAG_ROCE);
	struct mlx5_core_dev *dev0 = ldev->pf[0].dev;
	int err;

	err = mlx5_create_lag(ldev, tracker);
	if (err) {
		if (roce_lag) {
			mlx5_core_err(dev0,
				      "Failed to activate RoCE LAG\n");
		} else {
			mlx5_core_err(dev0,
				      "Failed to activate VF LAG\n"
				      "Make sure all VFs are unbound prior to VF LAG activation or deactivation\n");
		}
		return err;
	}

	ldev->flags |= flags;
	return 0;
}