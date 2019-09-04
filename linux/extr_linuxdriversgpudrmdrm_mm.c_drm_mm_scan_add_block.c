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
struct drm_mm_scan {scalar_t__ size; scalar_t__ mode; scalar_t__ alignment; scalar_t__ remainder_mask; scalar_t__ hit_start; scalar_t__ hit_end; int /*<<< orphan*/  range_end; int /*<<< orphan*/  range_start; int /*<<< orphan*/  color; struct drm_mm* mm; } ;
struct drm_mm_node {int scanned_block; int /*<<< orphan*/  node_list; int /*<<< orphan*/  allocated; struct drm_mm* mm; } ;
struct drm_mm {int /*<<< orphan*/  (* color_adjust ) (struct drm_mm_node*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ;int /*<<< orphan*/  scan_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_BUG_ON (int) ; 
 scalar_t__ DRM_MM_INSERT_HIGH ; 
 scalar_t__ __drm_mm_hole_node_end (struct drm_mm_node*) ; 
 scalar_t__ __drm_mm_hole_node_start (struct drm_mm_node*) ; 
 int /*<<< orphan*/  __list_del_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  div64_u64_rem (scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ likely (scalar_t__) ; 
 struct drm_mm_node* list_next_entry (struct drm_mm_node*,int /*<<< orphan*/ ) ; 
 struct drm_mm_node* list_prev_entry (struct drm_mm_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_list ; 
 int /*<<< orphan*/  stub1 (struct drm_mm_node*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

bool drm_mm_scan_add_block(struct drm_mm_scan *scan,
			   struct drm_mm_node *node)
{
	struct drm_mm *mm = scan->mm;
	struct drm_mm_node *hole;
	u64 hole_start, hole_end;
	u64 col_start, col_end;
	u64 adj_start, adj_end;

	DRM_MM_BUG_ON(node->mm != mm);
	DRM_MM_BUG_ON(!node->allocated);
	DRM_MM_BUG_ON(node->scanned_block);
	node->scanned_block = true;
	mm->scan_active++;

	/* Remove this block from the node_list so that we enlarge the hole
	 * (distance between the end of our previous node and the start of
	 * or next), without poisoning the link so that we can restore it
	 * later in drm_mm_scan_remove_block().
	 */
	hole = list_prev_entry(node, node_list);
	DRM_MM_BUG_ON(list_next_entry(hole, node_list) != node);
	__list_del_entry(&node->node_list);

	hole_start = __drm_mm_hole_node_start(hole);
	hole_end = __drm_mm_hole_node_end(hole);

	col_start = hole_start;
	col_end = hole_end;
	if (mm->color_adjust)
		mm->color_adjust(hole, scan->color, &col_start, &col_end);

	adj_start = max(col_start, scan->range_start);
	adj_end = min(col_end, scan->range_end);
	if (adj_end <= adj_start || adj_end - adj_start < scan->size)
		return false;

	if (scan->mode == DRM_MM_INSERT_HIGH)
		adj_start = adj_end - scan->size;

	if (scan->alignment) {
		u64 rem;

		if (likely(scan->remainder_mask))
			rem = adj_start & scan->remainder_mask;
		else
			div64_u64_rem(adj_start, scan->alignment, &rem);
		if (rem) {
			adj_start -= rem;
			if (scan->mode != DRM_MM_INSERT_HIGH)
				adj_start += scan->alignment;
			if (adj_start < max(col_start, scan->range_start) ||
			    min(col_end, scan->range_end) - adj_start < scan->size)
				return false;

			if (adj_end <= adj_start ||
			    adj_end - adj_start < scan->size)
				return false;
		}
	}

	scan->hit_start = adj_start;
	scan->hit_end = adj_start + scan->size;

	DRM_MM_BUG_ON(scan->hit_start >= scan->hit_end);
	DRM_MM_BUG_ON(scan->hit_start < hole_start);
	DRM_MM_BUG_ON(scan->hit_end > hole_end);

	return true;
}