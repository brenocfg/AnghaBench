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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int allocated; scalar_t__ size; scalar_t__ start; struct drm_mm* mm; int /*<<< orphan*/  node_list; } ;
struct drm_mm {scalar_t__ scan_active; TYPE_1__ head_node; int /*<<< orphan*/  holes_addr; void* holes_size; void* interval_tree; int /*<<< orphan*/  hole_stack; int /*<<< orphan*/ * color_adjust; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 void* RB_ROOT_CACHED ; 
 int /*<<< orphan*/  add_hole (TYPE_1__*) ; 

void drm_mm_init(struct drm_mm *mm, u64 start, u64 size)
{
	DRM_MM_BUG_ON(start + size <= start);

	mm->color_adjust = NULL;

	INIT_LIST_HEAD(&mm->hole_stack);
	mm->interval_tree = RB_ROOT_CACHED;
	mm->holes_size = RB_ROOT_CACHED;
	mm->holes_addr = RB_ROOT;

	/* Clever trick to avoid a special case in the free hole tracking. */
	INIT_LIST_HEAD(&mm->head_node.node_list);
	mm->head_node.allocated = false;
	mm->head_node.mm = mm;
	mm->head_node.start = start + size;
	mm->head_node.size = -size;
	add_hole(&mm->head_node);

	mm->scan_active = 0;
}