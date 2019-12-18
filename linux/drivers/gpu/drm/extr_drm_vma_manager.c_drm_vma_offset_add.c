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
struct drm_vma_offset_manager {int /*<<< orphan*/  vm_lock; int /*<<< orphan*/  vm_addr_space_mm; } ;

/* Variables and functions */
 int drm_mm_insert_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  drm_mm_node_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int drm_vma_offset_add(struct drm_vma_offset_manager *mgr,
		       struct drm_vma_offset_node *node, unsigned long pages)
{
	int ret = 0;

	write_lock(&mgr->vm_lock);

	if (!drm_mm_node_allocated(&node->vm_node))
		ret = drm_mm_insert_node(&mgr->vm_addr_space_mm,
					 &node->vm_node, pages);

	write_unlock(&mgr->vm_lock);

	return ret;
}