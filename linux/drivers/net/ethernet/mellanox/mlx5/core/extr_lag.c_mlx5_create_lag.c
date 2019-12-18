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
struct mlx5_lag {int /*<<< orphan*/ * v2p_map; TYPE_1__* pf; } ;
struct mlx5_core_dev {int dummy; } ;
struct lag_tracker {int dummy; } ;
struct TYPE_2__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int mlx5_cmd_create_lag (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_infer_tx_affinity_mapping (struct lag_tracker*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_create_lag(struct mlx5_lag *ldev,
			   struct lag_tracker *tracker)
{
	struct mlx5_core_dev *dev0 = ldev->pf[0].dev;
	int err;

	mlx5_infer_tx_affinity_mapping(tracker, &ldev->v2p_map[0],
				       &ldev->v2p_map[1]);

	mlx5_core_info(dev0, "lag map port 1:%d port 2:%d",
		       ldev->v2p_map[0], ldev->v2p_map[1]);

	err = mlx5_cmd_create_lag(dev0, ldev->v2p_map[0], ldev->v2p_map[1]);
	if (err)
		mlx5_core_err(dev0,
			      "Failed to create LAG (%d)\n",
			      err);
	return err;
}