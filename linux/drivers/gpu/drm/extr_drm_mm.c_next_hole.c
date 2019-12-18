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
struct drm_mm_node {int /*<<< orphan*/  hole_stack; int /*<<< orphan*/  rb_hole_addr; int /*<<< orphan*/  rb_hole_size; } ;
struct drm_mm {int /*<<< orphan*/  hole_stack; } ;
typedef  enum drm_mm_insert_mode { ____Placeholder_drm_mm_insert_mode } drm_mm_insert_mode ;

/* Variables and functions */
#define  DRM_MM_INSERT_BEST 131 
#define  DRM_MM_INSERT_EVICT 130 
#define  DRM_MM_INSERT_HIGH 129 
#define  DRM_MM_INSERT_LOW 128 
 int /*<<< orphan*/  hole_stack ; 
 struct drm_mm_node* list_next_entry (struct drm_mm_node*,int /*<<< orphan*/ ) ; 
 struct drm_mm_node* rb_hole_addr_to_node (int /*<<< orphan*/ ) ; 
 struct drm_mm_node* rb_hole_size_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_prev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_mm_node *
next_hole(struct drm_mm *mm,
	  struct drm_mm_node *node,
	  enum drm_mm_insert_mode mode)
{
	switch (mode) {
	default:
	case DRM_MM_INSERT_BEST:
		return rb_hole_size_to_node(rb_prev(&node->rb_hole_size));

	case DRM_MM_INSERT_LOW:
		return rb_hole_addr_to_node(rb_next(&node->rb_hole_addr));

	case DRM_MM_INSERT_HIGH:
		return rb_hole_addr_to_node(rb_prev(&node->rb_hole_addr));

	case DRM_MM_INSERT_EVICT:
		node = list_next_entry(node, hole_stack);
		return &node->hole_stack == &mm->hole_stack ? NULL : node;
	}
}