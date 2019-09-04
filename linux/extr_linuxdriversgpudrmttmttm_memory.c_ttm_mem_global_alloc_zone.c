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
typedef  int uint64_t ;
struct ttm_operation_ctx {scalar_t__ no_wait_gpu; } ;
struct ttm_mem_zone {int dummy; } ;
struct ttm_mem_global {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TTM_MEMORY_ALLOC_RETRIES ; 
 scalar_t__ ttm_mem_global_reserve (struct ttm_mem_global*,struct ttm_mem_zone*,int,int) ; 
 int /*<<< orphan*/  ttm_shrink (struct ttm_mem_global*,int,int,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_mem_global_alloc_zone(struct ttm_mem_global *glob,
				     struct ttm_mem_zone *single_zone,
				     uint64_t memory,
				     struct ttm_operation_ctx *ctx)
{
	int count = TTM_MEMORY_ALLOC_RETRIES;

	while (unlikely(ttm_mem_global_reserve(glob,
					       single_zone,
					       memory, true)
			!= 0)) {
		if (ctx->no_wait_gpu)
			return -ENOMEM;
		if (unlikely(count-- == 0))
			return -ENOMEM;
		ttm_shrink(glob, false, memory + (memory >> 2) + 16, ctx);
	}

	return 0;
}