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
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_bfreg_info {int ver; int /*<<< orphan*/  lock; int /*<<< orphan*/ * count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int NUM_NON_BLUE_FLAME_BFREGS ; 
 int alloc_high_class_bfreg (struct mlx5_ib_dev*,struct mlx5_bfreg_info*) ; 
 int alloc_med_class_bfreg (struct mlx5_ib_dev*,struct mlx5_bfreg_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_bfreg(struct mlx5_ib_dev *dev,
		       struct mlx5_bfreg_info *bfregi)
{
	int bfregn = -ENOMEM;

	mutex_lock(&bfregi->lock);
	if (bfregi->ver >= 2) {
		bfregn = alloc_high_class_bfreg(dev, bfregi);
		if (bfregn < 0)
			bfregn = alloc_med_class_bfreg(dev, bfregi);
	}

	if (bfregn < 0) {
		BUILD_BUG_ON(NUM_NON_BLUE_FLAME_BFREGS != 1);
		bfregn = 0;
		bfregi->count[bfregn]++;
	}
	mutex_unlock(&bfregi->lock);

	return bfregn;
}