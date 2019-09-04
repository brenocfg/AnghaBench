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
struct mlx5_lag {int allowed; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  mlx5_dev_list_lock () ; 
 int /*<<< orphan*/  mlx5_dev_list_unlock () ; 
 int /*<<< orphan*/  mlx5_do_bond (struct mlx5_lag*) ; 
 int /*<<< orphan*/  mlx5_lag_check_prereq (struct mlx5_lag*) ; 
 struct mlx5_lag* mlx5_lag_dev_get (struct mlx5_core_dev*) ; 
 int mlx5_lag_is_bonded (struct mlx5_lag*) ; 

__attribute__((used)) static int mlx5_lag_set_state(struct mlx5_core_dev *dev, bool allow)
{
	struct mlx5_lag *ldev;
	int ret = 0;
	bool lag_active;

	mlx5_dev_list_lock();

	ldev = mlx5_lag_dev_get(dev);
	if (!ldev) {
		ret = -ENODEV;
		goto unlock;
	}
	lag_active = mlx5_lag_is_bonded(ldev);
	if (!mlx5_lag_check_prereq(ldev) && allow) {
		ret = -EINVAL;
		goto unlock;
	}
	if (ldev->allowed == allow)
		goto unlock;
	ldev->allowed = allow;
	if ((lag_active && !allow) || allow)
		mlx5_do_bond(ldev);
unlock:
	mlx5_dev_list_unlock();
	return ret;
}