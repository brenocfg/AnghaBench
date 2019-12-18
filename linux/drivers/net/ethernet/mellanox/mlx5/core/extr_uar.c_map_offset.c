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
 int MLX5_ADAPTER_PAGE_SIZE ; 
 int MLX5_BFREGS_PER_UAR ; 
 unsigned long MLX5_BF_OFFSET ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_bf_reg_size ; 

__attribute__((used)) static unsigned long map_offset(struct mlx5_core_dev *mdev, int dbi)
{
	/* return the offset in bytes from the start of the page to the
	 * blue flame area of the UAR
	 */
	return dbi / MLX5_BFREGS_PER_UAR * MLX5_ADAPTER_PAGE_SIZE +
	       (dbi % MLX5_BFREGS_PER_UAR) *
	       (1 << MLX5_CAP_GEN(mdev, log_bf_reg_size)) + MLX5_BF_OFFSET;
}