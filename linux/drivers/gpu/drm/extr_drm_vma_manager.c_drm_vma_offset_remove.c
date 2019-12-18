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
struct drm_vma_offset_node {int /*<<< orphan*/  vm_node; } ;
struct drm_vma_offset_manager {int /*<<< orphan*/  vm_lock; } ;

/* Variables and functions */
 scalar_t__ drm_mm_node_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void drm_vma_offset_remove(struct drm_vma_offset_manager *mgr,
			   struct drm_vma_offset_node *node)
{
	write_lock(&mgr->vm_lock);

	if (drm_mm_node_allocated(&node->vm_node)) {
		drm_mm_remove_node(&node->vm_node);
		memset(&node->vm_node, 0, sizeof(node->vm_node));
	}

	write_unlock(&mgr->vm_lock);
}