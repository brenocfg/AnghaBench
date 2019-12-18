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
struct drm_mm_node {int allocated; int /*<<< orphan*/  rb_hole_addr; int /*<<< orphan*/  rb_hole_size; int /*<<< orphan*/  hole_stack; int /*<<< orphan*/  rb; int /*<<< orphan*/  node_list; struct drm_mm* mm; } ;
struct drm_mm {int /*<<< orphan*/  holes_addr; int /*<<< orphan*/  holes_size; int /*<<< orphan*/  interval_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_BUG_ON (int) ; 
 scalar_t__ drm_mm_hole_follows (struct drm_mm_node*) ; 
 int /*<<< orphan*/  list_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_replace_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_replace_node_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void drm_mm_replace_node(struct drm_mm_node *old, struct drm_mm_node *new)
{
	struct drm_mm *mm = old->mm;

	DRM_MM_BUG_ON(!old->allocated);

	*new = *old;

	list_replace(&old->node_list, &new->node_list);
	rb_replace_node_cached(&old->rb, &new->rb, &mm->interval_tree);

	if (drm_mm_hole_follows(old)) {
		list_replace(&old->hole_stack, &new->hole_stack);
		rb_replace_node_cached(&old->rb_hole_size,
				       &new->rb_hole_size,
				       &mm->holes_size);
		rb_replace_node(&old->rb_hole_addr,
				&new->rb_hole_addr,
				&mm->holes_addr);
	}

	old->allocated = false;
	new->allocated = true;
}