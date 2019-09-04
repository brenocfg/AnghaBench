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
typedef  size_t u8 ;
struct ice_sched_node {size_t num_children; scalar_t__ tx_sched_layer; struct ice_sched_node** children; } ;
struct ice_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool
ice_sched_find_node_in_subtree(struct ice_hw *hw, struct ice_sched_node *base,
			       struct ice_sched_node *node)
{
	u8 i;

	for (i = 0; i < base->num_children; i++) {
		struct ice_sched_node *child = base->children[i];

		if (node == child)
			return true;

		if (child->tx_sched_layer > node->tx_sched_layer)
			return false;

		/* this recursion is intentional, and wouldn't
		 * go more than 8 calls
		 */
		if (ice_sched_find_node_in_subtree(hw, child, node))
			return true;
	}
	return false;
}