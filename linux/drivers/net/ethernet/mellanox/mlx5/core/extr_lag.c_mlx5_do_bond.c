#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lag_tracker {scalar_t__ is_bonded; } ;
struct mlx5_lag {struct lag_tracker tracker; TYPE_1__* pf; } ;
struct TYPE_6__ {TYPE_2__* eswitch; } ;
struct mlx5_core_dev {TYPE_3__ priv; } ;
struct TYPE_5__ {scalar_t__ mode; } ;
struct TYPE_4__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_NONE ; 
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int /*<<< orphan*/  MLX5_LAG_FLAG_ROCE ; 
 int /*<<< orphan*/  MLX5_LAG_FLAG_SRIOV ; 
 scalar_t__ __mlx5_lag_is_active (struct mlx5_lag*) ; 
 int __mlx5_lag_is_roce (struct mlx5_lag*) ; 
 int /*<<< orphan*/  lag_mutex ; 
 int mlx5_activate_lag (struct mlx5_lag*,struct lag_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_add_dev_by_protocol (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_deactivate_lag (struct mlx5_lag*) ; 
 int /*<<< orphan*/  mlx5_lag_add_ib_devices (struct mlx5_lag*) ; 
 scalar_t__ mlx5_lag_check_prereq (struct mlx5_lag*) ; 
 int /*<<< orphan*/  mlx5_lag_remove_ib_devices (struct mlx5_lag*) ; 
 int /*<<< orphan*/  mlx5_modify_lag (struct mlx5_lag*,struct lag_tracker*) ; 
 int /*<<< orphan*/  mlx5_nic_vport_disable_roce (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_nic_vport_enable_roce (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_remove_dev_by_protocol (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_sriov_is_enabled (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_do_bond(struct mlx5_lag *ldev)
{
	struct mlx5_core_dev *dev0 = ldev->pf[0].dev;
	struct mlx5_core_dev *dev1 = ldev->pf[1].dev;
	struct lag_tracker tracker;
	bool do_bond, roce_lag;
	int err;

	if (!dev0 || !dev1)
		return;

	mutex_lock(&lag_mutex);
	tracker = ldev->tracker;
	mutex_unlock(&lag_mutex);

	do_bond = tracker.is_bonded && mlx5_lag_check_prereq(ldev);

	if (do_bond && !__mlx5_lag_is_active(ldev)) {
		roce_lag = !mlx5_sriov_is_enabled(dev0) &&
			   !mlx5_sriov_is_enabled(dev1);

#ifdef CONFIG_MLX5_ESWITCH
		roce_lag &= dev0->priv.eswitch->mode == MLX5_ESWITCH_NONE &&
			    dev1->priv.eswitch->mode == MLX5_ESWITCH_NONE;
#endif

		if (roce_lag)
			mlx5_lag_remove_ib_devices(ldev);

		err = mlx5_activate_lag(ldev, &tracker,
					roce_lag ? MLX5_LAG_FLAG_ROCE :
					MLX5_LAG_FLAG_SRIOV);
		if (err) {
			if (roce_lag)
				mlx5_lag_add_ib_devices(ldev);

			return;
		}

		if (roce_lag) {
			mlx5_add_dev_by_protocol(dev0, MLX5_INTERFACE_PROTOCOL_IB);
			mlx5_nic_vport_enable_roce(dev1);
		}
	} else if (do_bond && __mlx5_lag_is_active(ldev)) {
		mlx5_modify_lag(ldev, &tracker);
	} else if (!do_bond && __mlx5_lag_is_active(ldev)) {
		roce_lag = __mlx5_lag_is_roce(ldev);

		if (roce_lag) {
			mlx5_remove_dev_by_protocol(dev0, MLX5_INTERFACE_PROTOCOL_IB);
			mlx5_nic_vport_disable_roce(dev1);
		}

		err = mlx5_deactivate_lag(ldev);
		if (err)
			return;

		if (roce_lag)
			mlx5_lag_add_ib_devices(ldev);
	}
}