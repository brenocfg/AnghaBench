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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ice_sched_node {size_t tx_sched_layer; scalar_t__ num_children; struct ice_sched_node* sibling; } ;
struct ice_port_info {struct ice_hw* hw; } ;
struct ice_hw {scalar_t__ sw_entry_point_layer; scalar_t__* max_children; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_CFG ; 
 int ICE_ERR_PARAM ; 
 int ice_sched_add_elems (struct ice_port_info*,struct ice_sched_node*,struct ice_sched_node*,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ice_status
ice_sched_add_nodes_to_layer(struct ice_port_info *pi,
			     struct ice_sched_node *tc_node,
			     struct ice_sched_node *parent, u8 layer,
			     u16 num_nodes, u32 *first_node_teid,
			     u16 *num_nodes_added)
{
	u32 *first_teid_ptr = first_node_teid;
	u16 new_num_nodes, max_child_nodes;
	enum ice_status status = 0;
	struct ice_hw *hw = pi->hw;
	u16 num_added = 0;
	u32 temp;

	*num_nodes_added = 0;

	if (!num_nodes)
		return status;

	if (!parent || layer < hw->sw_entry_point_layer)
		return ICE_ERR_PARAM;

	/* max children per node per layer */
	max_child_nodes = hw->max_children[parent->tx_sched_layer];

	/* current number of children + required nodes exceed max children ? */
	if ((parent->num_children + num_nodes) > max_child_nodes) {
		/* Fail if the parent is a TC node */
		if (parent == tc_node)
			return ICE_ERR_CFG;

		/* utilize all the spaces if the parent is not full */
		if (parent->num_children < max_child_nodes) {
			new_num_nodes = max_child_nodes - parent->num_children;
			/* this recursion is intentional, and wouldn't
			 * go more than 2 calls
			 */
			status = ice_sched_add_nodes_to_layer(pi, tc_node,
							      parent, layer,
							      new_num_nodes,
							      first_node_teid,
							      &num_added);
			if (status)
				return status;

			*num_nodes_added += num_added;
		}
		/* Don't modify the first node TEID memory if the first node was
		 * added already in the above call. Instead send some temp
		 * memory for all other recursive calls.
		 */
		if (num_added)
			first_teid_ptr = &temp;

		new_num_nodes = num_nodes - num_added;

		/* This parent is full, try the next sibling */
		parent = parent->sibling;

		/* this recursion is intentional, for 1024 queues
		 * per VSI, it goes max of 16 iterations.
		 * 1024 / 8 = 128 layer 8 nodes
		 * 128 /8 = 16 (add 8 nodes per iteration)
		 */
		status = ice_sched_add_nodes_to_layer(pi, tc_node, parent,
						      layer, new_num_nodes,
						      first_teid_ptr,
						      &num_added);
		*num_nodes_added += num_added;
		return status;
	}

	status = ice_sched_add_elems(pi, tc_node, parent, layer, num_nodes,
				     num_nodes_added, first_node_teid);
	return status;
}