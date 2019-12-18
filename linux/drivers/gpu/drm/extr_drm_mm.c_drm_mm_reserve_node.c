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
typedef  scalar_t__ u64 ;
struct drm_mm_node {scalar_t__ start; scalar_t__ size; scalar_t__ hole_size; int allocated; int /*<<< orphan*/  node_list; struct drm_mm* mm; int /*<<< orphan*/  color; } ;
struct drm_mm {int /*<<< orphan*/  (* color_adjust ) (struct drm_mm_node*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ __drm_mm_hole_node_start (struct drm_mm_node*) ; 
 int /*<<< orphan*/  add_hole (struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_interval_tree_add_node (struct drm_mm_node*,struct drm_mm_node*) ; 
 struct drm_mm_node* find_hole (struct drm_mm*,scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_hole (struct drm_mm_node*) ; 
 int /*<<< orphan*/  save_stack (struct drm_mm_node*) ; 
 int /*<<< orphan*/  stub1 (struct drm_mm_node*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

int drm_mm_reserve_node(struct drm_mm *mm, struct drm_mm_node *node)
{
	u64 end = node->start + node->size;
	struct drm_mm_node *hole;
	u64 hole_start, hole_end;
	u64 adj_start, adj_end;

	end = node->start + node->size;
	if (unlikely(end <= node->start))
		return -ENOSPC;

	/* Find the relevant hole to add our node to */
	hole = find_hole(mm, node->start);
	if (!hole)
		return -ENOSPC;

	adj_start = hole_start = __drm_mm_hole_node_start(hole);
	adj_end = hole_end = hole_start + hole->hole_size;

	if (mm->color_adjust)
		mm->color_adjust(hole, node->color, &adj_start, &adj_end);

	if (adj_start > node->start || adj_end < end)
		return -ENOSPC;

	node->mm = mm;

	list_add(&node->node_list, &hole->node_list);
	drm_mm_interval_tree_add_node(hole, node);
	node->allocated = true;
	node->hole_size = 0;

	rm_hole(hole);
	if (node->start > hole_start)
		add_hole(hole);
	if (end < hole_end)
		add_hole(node);

	save_stack(node);
	return 0;
}