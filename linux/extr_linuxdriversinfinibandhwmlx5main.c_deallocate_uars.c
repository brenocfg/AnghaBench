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
struct mlx5_bfreg_info {int num_sys_pages; int num_static_sys_pages; scalar_t__* sys_pages; } ;
struct mlx5_ib_ucontext {struct mlx5_bfreg_info bfregi; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_IB_INVALID_UAR_INDEX ; 
 int /*<<< orphan*/  mlx5_cmd_free_uar (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void deallocate_uars(struct mlx5_ib_dev *dev,
			    struct mlx5_ib_ucontext *context)
{
	struct mlx5_bfreg_info *bfregi;
	int i;

	bfregi = &context->bfregi;
	for (i = 0; i < bfregi->num_sys_pages; i++)
		if (i < bfregi->num_static_sys_pages ||
		    bfregi->sys_pages[i] != MLX5_IB_INVALID_UAR_INDEX)
			mlx5_cmd_free_uar(dev->mdev, bfregi->sys_pages[i]);
}