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
 struct drm_mm_node* list_next_entry (struct drm_mm_node const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_list ; 

__attribute__((used)) static void separate_adjacent_colors(const struct drm_mm_node *node,
				     unsigned long color,
				     u64 *start,
				     u64 *end)
{
	if (node->allocated && node->color != color)
		++*start;

	node = list_next_entry(node, node_list);
	if (node->allocated && node->color != color)
		--*end;
}