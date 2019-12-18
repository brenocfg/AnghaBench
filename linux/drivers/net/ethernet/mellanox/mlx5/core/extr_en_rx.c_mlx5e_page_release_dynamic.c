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
struct mlx5e_rq {int /*<<< orphan*/  page_pool; } ;
struct mlx5e_dma_info {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx5e_page_dma_unmap (struct mlx5e_rq*,struct mlx5e_dma_info*) ; 
 scalar_t__ mlx5e_rx_cache_put (struct mlx5e_rq*,struct mlx5e_dma_info*) ; 
 int /*<<< orphan*/  page_pool_recycle_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pool_release_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

void mlx5e_page_release_dynamic(struct mlx5e_rq *rq,
				struct mlx5e_dma_info *dma_info,
				bool recycle)
{
	if (likely(recycle)) {
		if (mlx5e_rx_cache_put(rq, dma_info))
			return;

		mlx5e_page_dma_unmap(rq, dma_info);
		page_pool_recycle_direct(rq->page_pool, dma_info->page);
	} else {
		mlx5e_page_dma_unmap(rq, dma_info);
		page_pool_release_page(rq->page_pool, dma_info->page);
		put_page(dma_info->page);
	}
}