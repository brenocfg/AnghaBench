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
struct ttm_mem_reg {scalar_t__ mem_type; int num_pages; struct drm_mm_node* mm_node; } ;
struct drm_mm_node {int size; int start; } ;
struct TYPE_2__ {int visible_vram_size; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ TTM_PL_SYSTEM ; 
 scalar_t__ TTM_PL_TT ; 
 scalar_t__ TTM_PL_VRAM ; 

__attribute__((used)) static bool amdgpu_mem_visible(struct amdgpu_device *adev,
			       struct ttm_mem_reg *mem)
{
	struct drm_mm_node *nodes = mem->mm_node;

	if (mem->mem_type == TTM_PL_SYSTEM ||
	    mem->mem_type == TTM_PL_TT)
		return true;
	if (mem->mem_type != TTM_PL_VRAM)
		return false;

	/* ttm_mem_reg_ioremap only supports contiguous memory */
	if (nodes->size != mem->num_pages)
		return false;

	return ((nodes->start + nodes->size) << PAGE_SHIFT)
		<= adev->gmc.visible_vram_size;
}