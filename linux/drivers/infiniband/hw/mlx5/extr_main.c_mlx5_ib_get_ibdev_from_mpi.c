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
struct mlx5_ib_multiport_info {struct mlx5_ib_dev* ibdev; } ;
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_ib_multiport_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct mlx5_ib_dev *mlx5_ib_get_ibdev_from_mpi(struct mlx5_ib_multiport_info *mpi)
{
	struct mlx5_ib_dev *dev;

	mutex_lock(&mlx5_ib_multiport_mutex);
	dev = mpi->ibdev;
	mutex_unlock(&mlx5_ib_multiport_mutex);
	return dev;
}