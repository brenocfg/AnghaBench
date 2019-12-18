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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_cmd_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_cmd_teardown_hca (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_disable_hca (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_reclaim_startup_pages (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_stop_health_poll (struct mlx5_core_dev*,int) ; 

__attribute__((used)) static int mlx5_function_teardown(struct mlx5_core_dev *dev, bool boot)
{
	int err;

	mlx5_stop_health_poll(dev, boot);
	err = mlx5_cmd_teardown_hca(dev);
	if (err) {
		mlx5_core_err(dev, "tear_down_hca failed, skip cleanup\n");
		return err;
	}
	mlx5_reclaim_startup_pages(dev);
	mlx5_core_disable_hca(dev, 0);
	mlx5_cmd_cleanup(dev);

	return 0;
}