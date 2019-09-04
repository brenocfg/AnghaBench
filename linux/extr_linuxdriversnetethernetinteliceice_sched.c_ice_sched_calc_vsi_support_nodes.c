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
struct ice_sched_node {scalar_t__ num_children; struct ice_sched_node* sibling; } ;
struct ice_hw {size_t sw_entry_point_layer; TYPE_1__* layer_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_children; } ;

/* Variables and functions */
 struct ice_sched_node* ice_sched_get_first_node (struct ice_hw*,struct ice_sched_node*,size_t) ; 
 size_t ice_sched_get_vsi_layer (struct ice_hw*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_sched_calc_vsi_support_nodes(struct ice_hw *hw,
				 struct ice_sched_node *tc_node, u16 *num_nodes)
{
	struct ice_sched_node *node;
	u16 max_child;
	u8 i, vsil;

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
			node = ice_sched_get_first_node(hw, tc_node, i);
			max_child = le16_to_cpu(hw->layer_info[i].max_children);

			/* scan all the siblings */
			while (node) {
				if (node->num_children < max_child)
					break;
				node = node->sibling;
			}

			/* all the nodes are full, allocate a new one */
			if (!node)
				num_nodes[i]++;
		}
}