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
typedef  int /*<<< orphan*/  u32 ;
struct ib_pd {int dummy; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MR_TYPE_INTEGRITY ; 
 struct ib_mr* __mlx5_ib_alloc_mr (struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ib_mr *mlx5_ib_alloc_mr_integrity(struct ib_pd *pd,
					 u32 max_num_sg, u32 max_num_meta_sg)
{
	return __mlx5_ib_alloc_mr(pd, IB_MR_TYPE_INTEGRITY, max_num_sg,
				  max_num_meta_sg);
}