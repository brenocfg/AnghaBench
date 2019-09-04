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
struct drm_mm_node {int allocated; int scanned_block; int /*<<< orphan*/  node_list; struct drm_mm* mm; } ;
struct drm_mm {int /*<<< orphan*/  interval_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_BUG_ON (int) ; 
 int /*<<< orphan*/  add_hole (struct drm_mm_node*) ; 
 scalar_t__ drm_mm_hole_follows (struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_interval_tree_remove (struct drm_mm_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct drm_mm_node* list_prev_entry (struct drm_mm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_list ; 
 int /*<<< orphan*/  rm_hole (struct drm_mm_node*) ; 

void drm_mm_remove_node(struct drm_mm_node *node)
{
	struct drm_mm *mm = node->mm;
	struct drm_mm_node *prev_node;

	DRM_MM_BUG_ON(!node->allocated);
	DRM_MM_BUG_ON(node->scanned_block);

	prev_node = list_prev_entry(node, node_list);

	if (drm_mm_hole_follows(node))
		rm_hole(node);

	drm_mm_interval_tree_remove(node, &mm->interval_tree);
	list_del(&node->node_list);
	node->allocated = false;

	if (drm_mm_hole_follows(prev_node))
		rm_hole(prev_node);
	add_hole(prev_node);
}