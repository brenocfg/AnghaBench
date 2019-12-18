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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MLX5_SEMAPHORE_SW_RESET ; 
 int /*<<< orphan*/  MLX5_VSC_LOCK ; 
 int /*<<< orphan*/  MLX5_VSC_SPACE_SCAN_CRSPACE ; 
 int /*<<< orphan*/  MLX5_VSC_UNLOCK ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_crdump_enabled (struct mlx5_core_dev*) ; 
 int mlx5_crdump_fill (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_vsc_gw_lock (struct mlx5_core_dev*) ; 
 int mlx5_vsc_gw_set_space (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_vsc_gw_unlock (struct mlx5_core_dev*) ; 
 int mlx5_vsc_sem_set_space (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5_crdump_collect(struct mlx5_core_dev *dev, u32 *cr_data)
{
	int ret;

	if (!mlx5_crdump_enabled(dev))
		return -ENODEV;

	ret = mlx5_vsc_gw_lock(dev);
	if (ret) {
		mlx5_core_warn(dev, "crdump: failed to lock vsc gw err %d\n",
			       ret);
		return ret;
	}
	/* Verify no other PF is running cr-dump or sw reset */
	ret = mlx5_vsc_sem_set_space(dev, MLX5_SEMAPHORE_SW_RESET,
				     MLX5_VSC_LOCK);
	if (ret) {
		mlx5_core_warn(dev, "Failed to lock SW reset semaphore\n");
		goto unlock_gw;
	}

	ret = mlx5_vsc_gw_set_space(dev, MLX5_VSC_SPACE_SCAN_CRSPACE, NULL);
	if (ret)
		goto unlock_sem;

	ret = mlx5_crdump_fill(dev, cr_data);

unlock_sem:
	mlx5_vsc_sem_set_space(dev, MLX5_SEMAPHORE_SW_RESET, MLX5_VSC_UNLOCK);
unlock_gw:
	mlx5_vsc_gw_unlock(dev);
	return ret;
}