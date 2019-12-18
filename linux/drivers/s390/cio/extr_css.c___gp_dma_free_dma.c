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
struct gen_pool_chunk {int end_addr; int start_addr; scalar_t__ phys_addr; } ;
struct gen_pool {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __gp_dma_free_dma(struct gen_pool *pool,
			      struct gen_pool_chunk *chunk, void *data)
{
	size_t chunk_size = chunk->end_addr - chunk->start_addr + 1;

	dma_free_coherent((struct device *) data, chunk_size,
			 (void *) chunk->start_addr,
			 (dma_addr_t) chunk->phys_addr);
}