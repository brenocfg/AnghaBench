#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wqe_data_seg {void* lkey; void* byte_count; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  local_dma_lkey; } ;
struct mlx5_ib_pd {TYPE_1__ ibpd; } ;
struct mlx5_ib_mr {int desc_size; int ndescs; int /*<<< orphan*/  desc_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_reg_data_seg(struct mlx5_wqe_data_seg *dseg,
			     struct mlx5_ib_mr *mr,
			     struct mlx5_ib_pd *pd)
{
	int bcount = mr->desc_size * mr->ndescs;

	dseg->addr = cpu_to_be64(mr->desc_map);
	dseg->byte_count = cpu_to_be32(ALIGN(bcount, 64));
	dseg->lkey = cpu_to_be32(pd->ibpd.local_dma_lkey);
}