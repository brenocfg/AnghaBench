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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ice_sched_node {size_t owner; struct ice_sched_node** children; struct ice_sched_node* sibling; } ;
struct ice_port_info {struct ice_hw* hw; } ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_CFG ; 
 int ice_sched_add_nodes_to_layer (struct ice_port_info*,struct ice_sched_node*,struct ice_sched_node*,size_t,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct ice_sched_node* ice_sched_find_node_by_teid (struct ice_sched_node*,int /*<<< orphan*/ ) ; 
 size_t ice_sched_get_qgrp_layer (struct ice_hw*) ; 
 size_t ice_sched_get_vsi_layer (struct ice_hw*) ; 
 struct ice_sched_node* ice_sched_get_vsi_node (struct ice_hw*,struct ice_sched_node*,scalar_t__) ; 

__attribute__((used)) static enum ice_status
ice_sched_add_vsi_child_nodes(struct ice_port_info *pi, u16 vsi_handle,
			      struct ice_sched_node *tc_node, u16 *num_nodes,
			      u8 owner)
{
	struct ice_sched_node *parent, *node;
	struct ice_hw *hw = pi->hw;
	enum ice_status status;
	u32 first_node_teid;
	u16 num_added = 0;
	u8 i, qgl, vsil;

	qgl = ice_sched_get_qgrp_layer(hw);
	vsil = ice_sched_get_vsi_layer(hw);
	parent = ice_sched_get_vsi_node(hw, tc_node, vsi_handle);
	for (i = vsil + 1; i <= qgl; i++) {
		if (!parent)
			return ICE_ERR_CFG;

		status = ice_sched_add_nodes_to_layer(pi, tc_node, parent, i,
						      num_nodes[i],
						      &first_node_teid,
						      &num_added);
		if (status || num_nodes[i] != num_added)
			return ICE_ERR_CFG;

		/* The newly added node can be a new parent for the next
		 * layer nodes
		 */
		if (num_added) {
			parent = ice_sched_find_node_by_teid(tc_node,
							     first_node_teid);
			node = parent;
			while (node) {
				node->owner = owner;
				node = node->sibling;
			}
		} else {
			parent = parent->children[0];
		}
	}

	return 0;
}