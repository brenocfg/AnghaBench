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
typedef  scalar_t__ u8 ;
struct ice_sched_node {scalar_t__ num_children; scalar_t__ tx_sched_layer; struct ice_sched_node** children; } ;
struct ice_hw {scalar_t__ sw_entry_point_layer; } ;

/* Variables and functions */

__attribute__((used)) static struct ice_sched_node *
ice_sched_get_first_node(struct ice_hw *hw, struct ice_sched_node *parent,
			 u8 layer)
{
	u8 i;

	if (layer < hw->sw_entry_point_layer)
		return NULL;
	for (i = 0; i < parent->num_children; i++) {
		struct ice_sched_node *node = parent->children[i];

		if (node) {
			if (node->tx_sched_layer == layer)
				return node;
			/* this recursion is intentional, and wouldn't
			 * go more than 9 calls
			 */
			return ice_sched_get_first_node(hw, node, layer);
		}
	}
	return NULL;
}