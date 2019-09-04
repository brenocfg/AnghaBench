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
typedef  unsigned int u32 ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_bfreg_info {unsigned int num_sys_pages; unsigned int num_dyn_bfregs; scalar_t__* sys_pages; scalar_t__ num_static_sys_pages; int /*<<< orphan*/  lib_uar_4k; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLX5_IB_INVALID_UAR_INDEX ; 
 unsigned int MLX5_NON_FP_BFREGS_PER_UAR ; 
 unsigned int get_uars_per_sys_page (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*) ; 

int bfregn_to_uar_index(struct mlx5_ib_dev *dev,
			struct mlx5_bfreg_info *bfregi, u32 bfregn,
			bool dyn_bfreg)
{
	unsigned int bfregs_per_sys_page;
	u32 index_of_sys_page;
	u32 offset;

	bfregs_per_sys_page = get_uars_per_sys_page(dev, bfregi->lib_uar_4k) *
				MLX5_NON_FP_BFREGS_PER_UAR;
	index_of_sys_page = bfregn / bfregs_per_sys_page;

	if (dyn_bfreg) {
		index_of_sys_page += bfregi->num_static_sys_pages;

		if (index_of_sys_page >= bfregi->num_sys_pages)
			return -EINVAL;

		if (bfregn > bfregi->num_dyn_bfregs ||
		    bfregi->sys_pages[index_of_sys_page] == MLX5_IB_INVALID_UAR_INDEX) {
			mlx5_ib_dbg(dev, "Invalid dynamic uar index\n");
			return -EINVAL;
		}
	}

	offset = bfregn % bfregs_per_sys_page / MLX5_NON_FP_BFREGS_PER_UAR;
	return bfregi->sys_pages[index_of_sys_page] + offset;
}