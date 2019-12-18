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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_sched_node {scalar_t__ num_children; struct ice_sched_node* sibling; } ;
struct ice_hw {int sw_entry_point_layer; scalar_t__* max_children; int /*<<< orphan*/  port_info; } ;

/* Variables and functions */
 struct ice_sched_node* ice_sched_get_first_node (int /*<<< orphan*/ ,struct ice_sched_node*,int) ; 
 int ice_sched_get_vsi_layer (struct ice_hw*) ; 

__attribute__((used)) static void
ice_sched_calc_vsi_support_nodes(struct ice_hw *hw,
				 struct ice_sched_node *tc_node, u16 *num_nodes)
{
	struct ice_sched_node *node;
	u8 vsil;
	int i;

	vsil = ice_sched_get_vsi_layer(hw);
	for (i = vsil; i >= hw->sw_entry_point_layer; i--)
		/* Add intermediate nodes if TC has no children and
		 * need at least one node for VSI
		 */
		if (!tc_node->num_children || i == vsil) {
			num_nodes[i]++;
		} else {
			/* If intermediate nodes are reached max children
			 * then add a new one.
			 */
			node = ice_sched_get_first_node(hw->port_info, tc_node,
							(u8)i);
			/* scan all the siblings */
			while (node) {
				if (node->num_children < hw->max_children[i])
					break;
				node = node->sibling;
			}

			/* tree has one intermediate node to add this new VSI.
			 * So no need to calculate supported nodes for below
			 * layers.
			 */
			if (node)
				break;
			/* all the nodes are full, allocate a new one */
			num_nodes[i]++;
		}
}