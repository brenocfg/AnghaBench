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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ice_sched_node {scalar_t__ vsi_handle; struct ice_sched_node* sibling; } ;
struct ice_hw {int /*<<< orphan*/  port_info; } ;

/* Variables and functions */
 struct ice_sched_node* ice_sched_get_first_node (int /*<<< orphan*/ ,struct ice_sched_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_sched_get_vsi_layer (struct ice_hw*) ; 

__attribute__((used)) static struct ice_sched_node *
ice_sched_get_vsi_node(struct ice_hw *hw, struct ice_sched_node *tc_node,
		       u16 vsi_handle)
{
	struct ice_sched_node *node;
	u8 vsi_layer;

	vsi_layer = ice_sched_get_vsi_layer(hw);
	node = ice_sched_get_first_node(hw->port_info, tc_node, vsi_layer);

	/* Check whether it already exists */
	while (node) {
		if (node->vsi_handle == vsi_handle)
			return node;
		node = node->sibling;
	}

	return node;
}