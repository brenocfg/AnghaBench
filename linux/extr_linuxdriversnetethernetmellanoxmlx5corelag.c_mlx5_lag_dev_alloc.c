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
struct mlx5_lag {int /*<<< orphan*/  allowed; int /*<<< orphan*/  bond_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_lag* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_do_bond_work ; 
 int /*<<< orphan*/  mlx5_lag_check_prereq (struct mlx5_lag*) ; 

__attribute__((used)) static struct mlx5_lag *mlx5_lag_dev_alloc(void)
{
	struct mlx5_lag *ldev;

	ldev = kzalloc(sizeof(*ldev), GFP_KERNEL);
	if (!ldev)
		return NULL;

	INIT_DELAYED_WORK(&ldev->bond_work, mlx5_do_bond_work);
	ldev->allowed = mlx5_lag_check_prereq(ldev);

	return ldev;
}