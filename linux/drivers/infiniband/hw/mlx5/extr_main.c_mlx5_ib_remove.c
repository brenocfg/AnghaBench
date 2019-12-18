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
struct mlx5_ib_multiport_info {int /*<<< orphan*/  list; scalar_t__ ibdev; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  profile; } ;
typedef  void mlx5_core_dev ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_MANAGER (void*) ; 
 int /*<<< orphan*/  MLX5_IB_STAGE_MAX ; 
 int /*<<< orphan*/  __mlx5_ib_remove (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_multiport_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx5_core_is_mp_slave (void*) ; 
 int /*<<< orphan*/  mlx5_ib_multiport_mutex ; 
 int /*<<< orphan*/  mlx5_ib_unbind_slave_port (scalar_t__,struct mlx5_ib_multiport_info*) ; 
 int /*<<< orphan*/  mlx5_ib_unregister_vport_reps (void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_ib_remove(struct mlx5_core_dev *mdev, void *context)
{
	struct mlx5_ib_multiport_info *mpi;
	struct mlx5_ib_dev *dev;

	if (MLX5_ESWITCH_MANAGER(mdev) && context == mdev) {
		mlx5_ib_unregister_vport_reps(mdev);
		return;
	}

	if (mlx5_core_is_mp_slave(mdev)) {
		mpi = context;
		mutex_lock(&mlx5_ib_multiport_mutex);
		if (mpi->ibdev)
			mlx5_ib_unbind_slave_port(mpi->ibdev, mpi);
		list_del(&mpi->list);
		mutex_unlock(&mlx5_ib_multiport_mutex);
		kfree(mpi);
		return;
	}

	dev = context;
	__mlx5_ib_remove(dev, dev->profile, MLX5_IB_STAGE_MAX);
}