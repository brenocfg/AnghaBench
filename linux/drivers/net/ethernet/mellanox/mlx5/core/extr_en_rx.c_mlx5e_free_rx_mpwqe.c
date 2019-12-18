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
struct mlx5e_rq {int dummy; } ;
struct TYPE_2__ {struct mlx5e_dma_info* dma_info; } ;
struct mlx5e_mpw_info {int /*<<< orphan*/  xdp_xmit_bitmap; TYPE_1__ umr; } ;
struct mlx5e_dma_info {int dummy; } ;

/* Variables and functions */
 int MLX5_MPWRQ_PAGES_PER_WQE ; 
 int bitmap_empty (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bitmap_full (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5e_page_release (struct mlx5e_rq*,struct mlx5e_dma_info*,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx5e_free_rx_mpwqe(struct mlx5e_rq *rq, struct mlx5e_mpw_info *wi, bool recycle)
{
	bool no_xdp_xmit;
	struct mlx5e_dma_info *dma_info = wi->umr.dma_info;
	int i;

	/* A common case for AF_XDP. */
	if (bitmap_full(wi->xdp_xmit_bitmap, MLX5_MPWRQ_PAGES_PER_WQE))
		return;

	no_xdp_xmit = bitmap_empty(wi->xdp_xmit_bitmap,
				   MLX5_MPWRQ_PAGES_PER_WQE);

	for (i = 0; i < MLX5_MPWRQ_PAGES_PER_WQE; i++)
		if (no_xdp_xmit || !test_bit(i, wi->xdp_xmit_bitmap))
			mlx5e_page_release(rq, &dma_info[i], recycle);
}