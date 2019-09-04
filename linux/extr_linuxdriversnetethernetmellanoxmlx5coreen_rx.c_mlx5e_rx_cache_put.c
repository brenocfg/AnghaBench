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
typedef  int u32 ;
struct mlx5e_rq_stats {int /*<<< orphan*/  cache_waive; int /*<<< orphan*/  cache_full; } ;
struct mlx5e_page_cache {int tail; int head; struct mlx5e_dma_info* page_cache; } ;
struct mlx5e_rq {struct mlx5e_rq_stats* stats; struct mlx5e_page_cache page_cache; } ;
struct mlx5e_dma_info {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int MLX5E_CACHE_SIZE ; 
 int /*<<< orphan*/  mlx5e_page_is_reserved (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool mlx5e_rx_cache_put(struct mlx5e_rq *rq,
				      struct mlx5e_dma_info *dma_info)
{
	struct mlx5e_page_cache *cache = &rq->page_cache;
	u32 tail_next = (cache->tail + 1) & (MLX5E_CACHE_SIZE - 1);
	struct mlx5e_rq_stats *stats = rq->stats;

	if (tail_next == cache->head) {
		stats->cache_full++;
		return false;
	}

	if (unlikely(mlx5e_page_is_reserved(dma_info->page))) {
		stats->cache_waive++;
		return false;
	}

	cache->page_cache[cache->tail] = *dma_info;
	cache->tail = tail_next;
	return true;
}