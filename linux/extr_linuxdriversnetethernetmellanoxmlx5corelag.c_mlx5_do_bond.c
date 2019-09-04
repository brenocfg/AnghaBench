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
struct lag_tracker {scalar_t__ is_bonded; } ;
struct mlx5_lag {scalar_t__* v2p_map; TYPE_1__* pf; scalar_t__ allowed; struct lag_tracker tracker; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int MLX5_MAX_PORTS ; 
 int /*<<< orphan*/  lag_mutex ; 
 int /*<<< orphan*/  mlx5_activate_lag (struct mlx5_lag*,struct lag_tracker*) ; 
 int /*<<< orphan*/  mlx5_add_dev_by_protocol (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_modify_lag (struct mlx5_core_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_deactivate_lag (struct mlx5_lag*) ; 
 int /*<<< orphan*/  mlx5_infer_tx_affinity_mapping (struct lag_tracker*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ mlx5_lag_is_bonded (struct mlx5_lag*) ; 
 int /*<<< orphan*/  mlx5_nic_vport_disable_roce (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_nic_vport_enable_roce (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_remove_dev_by_protocol (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_do_bond(struct mlx5_lag *ldev)
{
	struct mlx5_core_dev *dev0 = ldev->pf[0].dev;
	struct mlx5_core_dev *dev1 = ldev->pf[1].dev;
	struct lag_tracker tracker;
	u8 v2p_port1, v2p_port2;
	int i, err;
	bool do_bond;

	if (!dev0 || !dev1)
		return;

	mutex_lock(&lag_mutex);
	tracker = ldev->tracker;
	mutex_unlock(&lag_mutex);

	do_bond = tracker.is_bonded && ldev->allowed;

	if (do_bond && !mlx5_lag_is_bonded(ldev)) {
		for (i = 0; i < MLX5_MAX_PORTS; i++)
			mlx5_remove_dev_by_protocol(ldev->pf[i].dev,
						    MLX5_INTERFACE_PROTOCOL_IB);

		mlx5_activate_lag(ldev, &tracker);

		mlx5_add_dev_by_protocol(dev0, MLX5_INTERFACE_PROTOCOL_IB);
		mlx5_nic_vport_enable_roce(dev1);
	} else if (do_bond && mlx5_lag_is_bonded(ldev)) {
		mlx5_infer_tx_affinity_mapping(&tracker, &v2p_port1,
					       &v2p_port2);

		if ((v2p_port1 != ldev->v2p_map[0]) ||
		    (v2p_port2 != ldev->v2p_map[1])) {
			ldev->v2p_map[0] = v2p_port1;
			ldev->v2p_map[1] = v2p_port2;

			err = mlx5_cmd_modify_lag(dev0, v2p_port1, v2p_port2);
			if (err)
				mlx5_core_err(dev0,
					      "Failed to modify LAG (%d)\n",
					      err);
		}
	} else if (!do_bond && mlx5_lag_is_bonded(ldev)) {
		mlx5_remove_dev_by_protocol(dev0, MLX5_INTERFACE_PROTOCOL_IB);
		mlx5_nic_vport_disable_roce(dev1);

		mlx5_deactivate_lag(ldev);

		for (i = 0; i < MLX5_MAX_PORTS; i++)
			if (ldev->pf[i].dev)
				mlx5_add_dev_by_protocol(ldev->pf[i].dev,
							 MLX5_INTERFACE_PROTOCOL_IB);
	}
}