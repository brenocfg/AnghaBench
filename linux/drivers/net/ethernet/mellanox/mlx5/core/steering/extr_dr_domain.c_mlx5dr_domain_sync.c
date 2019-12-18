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
typedef  int u32 ;
struct mlx5dr_domain {int /*<<< orphan*/  mdev; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int MLX5DR_DOMAIN_SYNC_FLAGS_HW ; 
 int MLX5DR_DOMAIN_SYNC_FLAGS_SW ; 
 int mlx5dr_cmd_sync_steering (int /*<<< orphan*/ ) ; 
 int mlx5dr_send_ring_force_drain (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5dr_domain_sync(struct mlx5dr_domain *dmn, u32 flags)
{
	int ret = 0;

	if (flags & MLX5DR_DOMAIN_SYNC_FLAGS_SW) {
		mutex_lock(&dmn->mutex);
		ret = mlx5dr_send_ring_force_drain(dmn);
		mutex_unlock(&dmn->mutex);
		if (ret)
			return ret;
	}

	if (flags & MLX5DR_DOMAIN_SYNC_FLAGS_HW)
		ret = mlx5dr_cmd_sync_steering(dmn->mdev);

	return ret;
}