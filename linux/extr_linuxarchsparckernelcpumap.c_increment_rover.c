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
struct cpuinfo_tree {struct cpuinfo_node* nodes; } ;
struct cpuinfo_node {int level; scalar_t__ rover; scalar_t__ child_end; scalar_t__ child_start; size_t parent_index; } ;

/* Variables and functions */
 int const ROVER_INC_PARENT_ON_LOOP ; 

__attribute__((used)) static void increment_rover(struct cpuinfo_tree *t, int node_index,
                            int root_index, const int *rover_inc_table)
{
	struct cpuinfo_node *node = &t->nodes[node_index];
	int top_level, level;

	top_level = t->nodes[root_index].level;
	for (level = node->level; level >= top_level; level--) {
		node->rover++;
		if (node->rover <= node->child_end)
			return;

		node->rover = node->child_start;
		/* If parent's rover does not need to be adjusted, stop here. */
		if ((level == top_level) ||
		    !(rover_inc_table[level] & ROVER_INC_PARENT_ON_LOOP))
			return;

		node = &t->nodes[node->parent_index];
	}
}