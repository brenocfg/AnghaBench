#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct ttm_mem_reg {size_t mem_type; } ;
struct ttm_buffer_object {TYPE_2__* bdev; } ;
struct drm_mm_node {int start; } ;
struct TYPE_4__ {TYPE_1__* man; } ;
struct TYPE_3__ {scalar_t__ gpu_offset; } ;

/* Variables and functions */
 int AMDGPU_BO_INVALID_OFFSET ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static uint64_t amdgpu_mm_node_addr(struct ttm_buffer_object *bo,
				    struct drm_mm_node *mm_node,
				    struct ttm_mem_reg *mem)
{
	uint64_t addr = 0;

	if (mm_node->start != AMDGPU_BO_INVALID_OFFSET) {
		addr = mm_node->start << PAGE_SHIFT;
		addr += bo->bdev->man[mem->mem_type].gpu_offset;
	}
	return addr;
}