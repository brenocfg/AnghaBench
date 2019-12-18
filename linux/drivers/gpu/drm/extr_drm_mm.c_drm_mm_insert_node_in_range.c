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
struct drm_mm_node {scalar_t__ hole_size; unsigned long color; int allocated; int /*<<< orphan*/  node_list; scalar_t__ start; scalar_t__ size; struct drm_mm* mm; } ;
struct drm_mm {int /*<<< orphan*/  (* color_adjust ) (struct drm_mm_node*,unsigned long,scalar_t__*,scalar_t__*) ;int /*<<< orphan*/  holes_size; } ;
typedef  enum drm_mm_insert_mode { ____Placeholder_drm_mm_insert_mode } drm_mm_insert_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_BUG_ON (int) ; 
 int DRM_MM_INSERT_HIGH ; 
 int DRM_MM_INSERT_LOW ; 
 int DRM_MM_INSERT_ONCE ; 
 int ENOSPC ; 
 scalar_t__ __drm_mm_hole_node_start (struct drm_mm_node*) ; 
 int /*<<< orphan*/  add_hole (struct drm_mm_node* const) ; 
 int /*<<< orphan*/  div64_u64_rem (scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  drm_mm_interval_tree_add_node (struct drm_mm_node*,struct drm_mm_node* const) ; 
 struct drm_mm_node* first_hole (struct drm_mm* const,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ is_power_of_2 (scalar_t__) ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct drm_mm_node* next_hole (struct drm_mm* const,struct drm_mm_node*,int) ; 
 int /*<<< orphan*/  rb_first_cached (int /*<<< orphan*/ *) ; 
 scalar_t__ rb_to_hole_size_or_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rm_hole (struct drm_mm_node*) ; 
 int /*<<< orphan*/  save_stack (struct drm_mm_node* const) ; 
 int /*<<< orphan*/  stub1 (struct drm_mm_node*,unsigned long,scalar_t__*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

int drm_mm_insert_node_in_range(struct drm_mm * const mm,
				struct drm_mm_node * const node,
				u64 size, u64 alignment,
				unsigned long color,
				u64 range_start, u64 range_end,
				enum drm_mm_insert_mode mode)
{
	struct drm_mm_node *hole;
	u64 remainder_mask;
	bool once;

	DRM_MM_BUG_ON(range_start > range_end);

	if (unlikely(size == 0 || range_end - range_start < size))
		return -ENOSPC;

	if (rb_to_hole_size_or_zero(rb_first_cached(&mm->holes_size)) < size)
		return -ENOSPC;

	if (alignment <= 1)
		alignment = 0;

	once = mode & DRM_MM_INSERT_ONCE;
	mode &= ~DRM_MM_INSERT_ONCE;

	remainder_mask = is_power_of_2(alignment) ? alignment - 1 : 0;
	for (hole = first_hole(mm, range_start, range_end, size, mode);
	     hole;
	     hole = once ? NULL : next_hole(mm, hole, mode)) {
		u64 hole_start = __drm_mm_hole_node_start(hole);
		u64 hole_end = hole_start + hole->hole_size;
		u64 adj_start, adj_end;
		u64 col_start, col_end;

		if (mode == DRM_MM_INSERT_LOW && hole_start >= range_end)
			break;

		if (mode == DRM_MM_INSERT_HIGH && hole_end <= range_start)
			break;

		col_start = hole_start;
		col_end = hole_end;
		if (mm->color_adjust)
			mm->color_adjust(hole, color, &col_start, &col_end);

		adj_start = max(col_start, range_start);
		adj_end = min(col_end, range_end);

		if (adj_end <= adj_start || adj_end - adj_start < size)
			continue;

		if (mode == DRM_MM_INSERT_HIGH)
			adj_start = adj_end - size;

		if (alignment) {
			u64 rem;

			if (likely(remainder_mask))
				rem = adj_start & remainder_mask;
			else
				div64_u64_rem(adj_start, alignment, &rem);
			if (rem) {
				adj_start -= rem;
				if (mode != DRM_MM_INSERT_HIGH)
					adj_start += alignment;

				if (adj_start < max(col_start, range_start) ||
				    min(col_end, range_end) - adj_start < size)
					continue;

				if (adj_end <= adj_start ||
				    adj_end - adj_start < size)
					continue;
			}
		}

		node->mm = mm;
		node->size = size;
		node->start = adj_start;
		node->color = color;
		node->hole_size = 0;

		list_add(&node->node_list, &hole->node_list);
		drm_mm_interval_tree_add_node(hole, node);
		node->allocated = true;

		rm_hole(hole);
		if (adj_start > hole_start)
			add_hole(hole);
		if (adj_start + size < hole_end)
			add_hole(node);

		save_stack(node);
		return 0;
	}

	return -ENOSPC;
}