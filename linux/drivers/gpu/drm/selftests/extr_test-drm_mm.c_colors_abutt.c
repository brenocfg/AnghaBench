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
struct drm_mm_node {int /*<<< orphan*/  size; int /*<<< orphan*/  start; int /*<<< orphan*/  color; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  start; int /*<<< orphan*/  color; scalar_t__ allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_hole_follows (struct drm_mm_node const*) ; 
 TYPE_1__* list_next_entry (struct drm_mm_node const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_list ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool colors_abutt(const struct drm_mm_node *node)
{
	if (!drm_mm_hole_follows(node) &&
	    list_next_entry(node, node_list)->allocated) {
		pr_err("colors abutt; %ld [%llx + %llx] is next to %ld [%llx + %llx]!\n",
		       node->color, node->start, node->size,
		       list_next_entry(node, node_list)->color,
		       list_next_entry(node, node_list)->start,
		       list_next_entry(node, node_list)->size);
		return true;
	}

	return false;
}