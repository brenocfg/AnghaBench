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
struct TYPE_2__ {int reserved; } ;
struct i915_ggtt {TYPE_1__ vm; } ;
struct drm_mm_node {int size; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  drm_mm_node_allocated (struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 

__attribute__((used)) static void vgt_deballoon_space(struct i915_ggtt *ggtt,
				struct drm_mm_node *node)
{
	if (!drm_mm_node_allocated(node))
		return;

	DRM_DEBUG_DRIVER("deballoon space: range [0x%llx - 0x%llx] %llu KiB.\n",
			 node->start,
			 node->start + node->size,
			 node->size / 1024);

	ggtt->vm.reserved -= node->size;
	drm_mm_remove_node(node);
}