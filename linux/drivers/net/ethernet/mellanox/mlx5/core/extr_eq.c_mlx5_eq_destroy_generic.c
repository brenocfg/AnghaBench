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
struct mlx5_eq {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mlx5_eq*) ; 
 int destroy_async_eq (struct mlx5_core_dev*,struct mlx5_eq*) ; 
 int /*<<< orphan*/  kvfree (struct mlx5_eq*) ; 

int mlx5_eq_destroy_generic(struct mlx5_core_dev *dev, struct mlx5_eq *eq)
{
	int err;

	if (IS_ERR(eq))
		return -EINVAL;

	err = destroy_async_eq(dev, eq);
	if (err)
		goto out;

	kvfree(eq);
out:
	return err;
}