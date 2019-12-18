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
typedef  scalar_t__ u8 ;
struct mlx5_lag {scalar_t__* v2p_map; TYPE_1__* pf; } ;
struct mlx5_core_dev {int dummy; } ;
struct lag_tracker {int dummy; } ;
struct TYPE_2__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int mlx5_cmd_modify_lag (struct mlx5_core_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_infer_tx_affinity_mapping (struct lag_tracker*,scalar_t__*,scalar_t__*) ; 

void mlx5_modify_lag(struct mlx5_lag *ldev,
		     struct lag_tracker *tracker)
{
	struct mlx5_core_dev *dev0 = ldev->pf[0].dev;
	u8 v2p_port1, v2p_port2;
	int err;

	mlx5_infer_tx_affinity_mapping(tracker, &v2p_port1,
				       &v2p_port2);

	if (v2p_port1 != ldev->v2p_map[0] ||
	    v2p_port2 != ldev->v2p_map[1]) {
		ldev->v2p_map[0] = v2p_port1;
		ldev->v2p_map[1] = v2p_port2;

		mlx5_core_info(dev0, "modify lag map port 1:%d port 2:%d",
			       ldev->v2p_map[0], ldev->v2p_map[1]);

		err = mlx5_cmd_modify_lag(dev0, v2p_port1, v2p_port2);
		if (err)
			mlx5_core_err(dev0,
				      "Failed to modify LAG (%d)\n",
				      err);
	}
}