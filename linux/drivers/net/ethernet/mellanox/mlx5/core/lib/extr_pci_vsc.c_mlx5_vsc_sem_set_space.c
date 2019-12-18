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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_vsc_state { ____Placeholder_mlx5_vsc_state } mlx5_vsc_state ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MLX5_SEMAPHORE_SPACE_DOMAIN ; 
 int MLX5_VSC_LOCK ; 
 int /*<<< orphan*/  VSC_COUNTER_OFFSET ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_vsc_gw_read (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int mlx5_vsc_gw_set_space (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5_vsc_gw_write (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int vsc_read (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 

int mlx5_vsc_sem_set_space(struct mlx5_core_dev *dev, u16 space,
			   enum mlx5_vsc_state state)
{
	u32 data, id = 0;
	int ret;

	ret = mlx5_vsc_gw_set_space(dev, MLX5_SEMAPHORE_SPACE_DOMAIN, NULL);
	if (ret) {
		mlx5_core_warn(dev, "Failed to set gw space %d\n", ret);
		return ret;
	}

	if (state == MLX5_VSC_LOCK) {
		/* Get a unique ID based on the counter */
		ret = vsc_read(dev, VSC_COUNTER_OFFSET, &id);
		if (ret)
			return ret;
	}

	/* Try to modify lock */
	ret = mlx5_vsc_gw_write(dev, space, id);
	if (ret)
		return ret;

	/* Verify lock was modified */
	ret = mlx5_vsc_gw_read(dev, space, &data);
	if (ret)
		return -EINVAL;

	if (data != id)
		return -EBUSY;

	return 0;
}