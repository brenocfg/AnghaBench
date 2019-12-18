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
struct TYPE_3__ {unsigned long base; } ;
struct TYPE_4__ {TYPE_1__ bus; } ;
struct ttm_buffer_object {TYPE_2__ mem; } ;
struct drm_mm_node {unsigned long start; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 struct drm_mm_node* amdgpu_find_mm_node (TYPE_2__*,unsigned long*) ; 

__attribute__((used)) static unsigned long amdgpu_ttm_io_mem_pfn(struct ttm_buffer_object *bo,
					   unsigned long page_offset)
{
	struct drm_mm_node *mm;
	unsigned long offset = (page_offset << PAGE_SHIFT);

	mm = amdgpu_find_mm_node(&bo->mem, &offset);
	return (bo->mem.bus.base >> PAGE_SHIFT) + mm->start +
		(offset >> PAGE_SHIFT);
}