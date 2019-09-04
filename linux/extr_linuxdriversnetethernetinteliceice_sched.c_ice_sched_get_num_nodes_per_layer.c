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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct ice_sched_node {struct ice_sched_node* sibling; } ;
struct ice_port_info {TYPE_1__* root; struct ice_hw* hw; } ;
struct ice_hw {int dummy; } ;
struct TYPE_2__ {size_t num_children; struct ice_sched_node** children; } ;

/* Variables and functions */
 struct ice_sched_node* ice_sched_get_first_node (struct ice_hw*,struct ice_sched_node*,size_t) ; 

__attribute__((used)) static u16
ice_sched_get_num_nodes_per_layer(struct ice_port_info *pi, u8 layer)
{
	struct ice_hw *hw;
	u16 num_nodes = 0;
	u8 i;

	if (!pi)
		return num_nodes;

	hw = pi->hw;

	/* Calculate the number of nodes for all TCs */
	for (i = 0; i < pi->root->num_children; i++) {
		struct ice_sched_node *tc_node, *node;

		tc_node = pi->root->children[i];

		/* Get the first node */
		node = ice_sched_get_first_node(hw, tc_node, layer);
		if (!node)
			continue;

		/* count the siblings */
		while (node) {
			num_nodes++;
			node = node->sibling;
		}
	}

	return num_nodes;
}