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
struct TYPE_2__ {int /*<<< orphan*/  map_dir; } ;
struct mlx5e_rq {int /*<<< orphan*/  page_pool; int /*<<< orphan*/  pdev; TYPE_1__ buff; } ;
struct mlx5e_dma_info {int /*<<< orphan*/ * page; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5e_rx_cache_get (struct mlx5e_rq*,struct mlx5e_dma_info*) ; 
 int /*<<< orphan*/ * page_pool_dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pool_recycle_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int mlx5e_page_alloc_pool(struct mlx5e_rq *rq,
					struct mlx5e_dma_info *dma_info)
{
	if (mlx5e_rx_cache_get(rq, dma_info))
		return 0;

	dma_info->page = page_pool_dev_alloc_pages(rq->page_pool);
	if (unlikely(!dma_info->page))
		return -ENOMEM;

	dma_info->addr = dma_map_page(rq->pdev, dma_info->page, 0,
				      PAGE_SIZE, rq->buff.map_dir);
	if (unlikely(dma_mapping_error(rq->pdev, dma_info->addr))) {
		page_pool_recycle_direct(rq->page_pool, dma_info->page);
		dma_info->page = NULL;
		return -ENOMEM;
	}

	return 0;
}