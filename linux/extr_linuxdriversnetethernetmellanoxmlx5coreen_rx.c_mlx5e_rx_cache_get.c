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
struct mlx5e_rq_stats {int /*<<< orphan*/  cache_reuse; int /*<<< orphan*/  cache_busy; int /*<<< orphan*/  cache_empty; } ;
struct mlx5e_page_cache {size_t head; size_t tail; struct mlx5e_dma_info* page_cache; } ;
struct mlx5e_rq {int /*<<< orphan*/  pdev; struct mlx5e_rq_stats* stats; struct mlx5e_page_cache page_cache; } ;
struct mlx5e_dma_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int MLX5E_CACHE_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int page_ref_count (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool mlx5e_rx_cache_get(struct mlx5e_rq *rq,
				      struct mlx5e_dma_info *dma_info)
{
	struct mlx5e_page_cache *cache = &rq->page_cache;
	struct mlx5e_rq_stats *stats = rq->stats;

	if (unlikely(cache->head == cache->tail)) {
		stats->cache_empty++;
		return false;
	}

	if (page_ref_count(cache->page_cache[cache->head].page) != 1) {
		stats->cache_busy++;
		return false;
	}

	*dma_info = cache->page_cache[cache->head];
	cache->head = (cache->head + 1) & (MLX5E_CACHE_SIZE - 1);
	stats->cache_reuse++;

	dma_sync_single_for_device(rq->pdev, dma_info->addr,
				   PAGE_SIZE,
				   DMA_FROM_DEVICE);
	return true;
}