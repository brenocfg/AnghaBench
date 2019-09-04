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
typedef  size_t uint32_t ;
struct ttm_place {int dummy; } ;
struct ttm_operation_ctx {int dummy; } ;
struct ttm_mem_type_manager {TYPE_1__* func; } ;
struct ttm_mem_reg {size_t mem_type; scalar_t__ mm_node; } ;
struct ttm_buffer_object {struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;
struct TYPE_2__ {int (* get_node ) (struct ttm_mem_type_manager*,struct ttm_buffer_object*,struct ttm_place const*,struct ttm_mem_reg*) ;} ;

/* Variables and functions */
 int stub1 (struct ttm_mem_type_manager*,struct ttm_buffer_object*,struct ttm_place const*,struct ttm_mem_reg*) ; 
 int ttm_bo_add_move_fence (struct ttm_buffer_object*,struct ttm_mem_type_manager*,struct ttm_mem_reg*) ; 
 int ttm_mem_evict_first (struct ttm_bo_device*,size_t,struct ttm_place const*,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_bo_mem_force_space(struct ttm_buffer_object *bo,
					uint32_t mem_type,
					const struct ttm_place *place,
					struct ttm_mem_reg *mem,
					struct ttm_operation_ctx *ctx)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_mem_type_manager *man = &bdev->man[mem_type];
	int ret;

	do {
		ret = (*man->func->get_node)(man, bo, place, mem);
		if (unlikely(ret != 0))
			return ret;
		if (mem->mm_node)
			break;
		ret = ttm_mem_evict_first(bdev, mem_type, place, ctx);
		if (unlikely(ret != 0))
			return ret;
	} while (1);
	mem->mem_type = mem_type;
	return ttm_bo_add_move_fence(bo, man, mem);
}