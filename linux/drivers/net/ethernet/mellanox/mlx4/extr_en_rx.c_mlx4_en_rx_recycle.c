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
struct mlx4_en_page_cache {size_t index; TYPE_1__* buf; } ;
struct mlx4_en_rx_ring {struct mlx4_en_page_cache page_cache; } ;
struct mlx4_en_rx_alloc {int /*<<< orphan*/  dma; int /*<<< orphan*/  page; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 size_t MLX4_EN_CACHE_SIZE ; 

bool mlx4_en_rx_recycle(struct mlx4_en_rx_ring *ring,
			struct mlx4_en_rx_alloc *frame)
{
	struct mlx4_en_page_cache *cache = &ring->page_cache;

	if (cache->index >= MLX4_EN_CACHE_SIZE)
		return false;

	cache->buf[cache->index].page = frame->page;
	cache->buf[cache->index].dma = frame->dma;
	cache->index++;
	return true;
}