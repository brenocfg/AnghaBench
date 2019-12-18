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
struct mlx5_ib_dev {int /*<<< orphan*/  fp_bfreg; int /*<<< orphan*/  mdev; int /*<<< orphan*/  bfreg; } ;

/* Variables and functions */
 int mlx5_alloc_bfreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mlx5_free_bfreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_ib_stage_bfrag_init(struct mlx5_ib_dev *dev)
{
	int err;

	err = mlx5_alloc_bfreg(dev->mdev, &dev->bfreg, false, false);
	if (err)
		return err;

	err = mlx5_alloc_bfreg(dev->mdev, &dev->fp_bfreg, false, true);
	if (err)
		mlx5_free_bfreg(dev->mdev, &dev->fp_bfreg);

	return err;
}