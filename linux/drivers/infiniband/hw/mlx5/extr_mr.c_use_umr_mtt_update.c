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
typedef  int u64 ;
struct mlx5_ib_mr {int order; } ;

/* Variables and functions */
 int MLX5_ADAPTER_PAGE_SIZE ; 

__attribute__((used)) static bool use_umr_mtt_update(struct mlx5_ib_mr *mr, u64 start, u64 length)
{
	return ((u64)1 << mr->order) * MLX5_ADAPTER_PAGE_SIZE >=
		length + (start & (MLX5_ADAPTER_PAGE_SIZE - 1));
}