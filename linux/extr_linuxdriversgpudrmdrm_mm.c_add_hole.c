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
struct drm_mm_node {int /*<<< orphan*/  hole_stack; scalar_t__ hole_size; struct drm_mm* mm; } ;
struct drm_mm {int /*<<< orphan*/  hole_stack; int /*<<< orphan*/  holes_addr; int /*<<< orphan*/  holes_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_BUG_ON (int) ; 
 int /*<<< orphan*/  HOLE_ADDR ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __drm_mm_hole_node_end (struct drm_mm_node*) ; 
 scalar_t__ __drm_mm_hole_node_start (struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_hole_follows (struct drm_mm_node*) ; 
 int /*<<< orphan*/  insert_hole_size (int /*<<< orphan*/ *,struct drm_mm_node*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_hole_addr ; 

__attribute__((used)) static void add_hole(struct drm_mm_node *node)
{
	struct drm_mm *mm = node->mm;

	node->hole_size =
		__drm_mm_hole_node_end(node) - __drm_mm_hole_node_start(node);
	DRM_MM_BUG_ON(!drm_mm_hole_follows(node));

	insert_hole_size(&mm->holes_size, node);
	RB_INSERT(mm->holes_addr, rb_hole_addr, HOLE_ADDR);

	list_add(&node->hole_stack, &mm->hole_stack);
}