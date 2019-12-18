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
struct mlx5_uars_page {unsigned int map; } ;
struct mlx5_sq_bfreg {unsigned int map; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 unsigned int MLX5_ADAPTER_PAGE_SHIFT ; 
 uintptr_t MLX5_ADAPTER_PAGE_SIZE ; 
 unsigned int MLX5_BFREGS_PER_UAR ; 
 uintptr_t MLX5_BF_OFFSET ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_bf_reg_size ; 

__attribute__((used)) static unsigned int addr_to_dbi_in_syspage(struct mlx5_core_dev *dev,
					   struct mlx5_uars_page *up,
					   struct mlx5_sq_bfreg *bfreg)
{
	unsigned int uar_idx;
	unsigned int bfreg_idx;
	unsigned int bf_reg_size;

	bf_reg_size = 1 << MLX5_CAP_GEN(dev, log_bf_reg_size);

	uar_idx = (bfreg->map - up->map) >> MLX5_ADAPTER_PAGE_SHIFT;
	bfreg_idx = (((uintptr_t)bfreg->map % MLX5_ADAPTER_PAGE_SIZE) - MLX5_BF_OFFSET) / bf_reg_size;

	return uar_idx * MLX5_BFREGS_PER_UAR + bfreg_idx;
}