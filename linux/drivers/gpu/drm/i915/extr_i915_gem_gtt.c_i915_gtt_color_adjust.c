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
typedef  int /*<<< orphan*/  u64 ;
struct drm_mm_node {unsigned long color; scalar_t__ allocated; } ;

/* Variables and functions */
 scalar_t__ I915_GTT_PAGE_SIZE ; 
 struct drm_mm_node* list_next_entry (struct drm_mm_node const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_list ; 

__attribute__((used)) static void i915_gtt_color_adjust(const struct drm_mm_node *node,
				  unsigned long color,
				  u64 *start,
				  u64 *end)
{
	if (node->allocated && node->color != color)
		*start += I915_GTT_PAGE_SIZE;

	/* Also leave a space between the unallocated reserved node after the
	 * GTT and any objects within the GTT, i.e. we use the color adjustment
	 * to insert a guard page to prevent prefetches crossing over the
	 * GTT boundary.
	 */
	node = list_next_entry(node, node_list);
	if (node->color != color)
		*end -= I915_GTT_PAGE_SIZE;
}