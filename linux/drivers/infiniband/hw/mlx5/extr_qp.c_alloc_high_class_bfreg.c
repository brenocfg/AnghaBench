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
struct mlx5_bfreg_info {int /*<<< orphan*/ * count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int first_hi_bfreg (struct mlx5_ib_dev*,struct mlx5_bfreg_info*) ; 
 int max_bfregs (struct mlx5_ib_dev*,struct mlx5_bfreg_info*) ; 

__attribute__((used)) static int alloc_high_class_bfreg(struct mlx5_ib_dev *dev,
				  struct mlx5_bfreg_info *bfregi)
{
	int i;

	for (i = first_hi_bfreg(dev, bfregi); i < max_bfregs(dev, bfregi); i++) {
		if (!bfregi->count[i]) {
			bfregi->count[i]++;
			return i;
		}
	}

	return -ENOMEM;
}