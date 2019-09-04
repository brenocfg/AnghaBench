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
typedef  scalar_t__ u16 ;
struct ice_sched_node {size_t owner; int /*<<< orphan*/  num_children; struct ice_sched_node* sibling; } ;
struct ice_port_info {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_free_sched_node (struct ice_port_info*,struct ice_sched_node*) ; 
 struct ice_sched_node* ice_sched_get_first_node (int /*<<< orphan*/ ,struct ice_sched_node*,size_t) ; 
 size_t ice_sched_get_qgrp_layer (int /*<<< orphan*/ ) ; 
 size_t ice_sched_get_vsi_layer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_sched_rm_vsi_child_nodes(struct ice_port_info *pi,
			     struct ice_sched_node *vsi_node, u16 *num_nodes,
			     u8 owner)
{
	struct ice_sched_node *node, *next;
	u8 i, qgl, vsil;
	u16 num;

	qgl = ice_sched_get_qgrp_layer(pi->hw);
	vsil = ice_sched_get_vsi_layer(pi->hw);

	for (i = qgl; i > vsil; i--) {
		num = num_nodes[i];
		node = ice_sched_get_first_node(pi->hw, vsi_node, i);
		while (node && num) {
			next = node->sibling;
			if (node->owner == owner && !node->num_children) {
				ice_free_sched_node(pi, node);
				num--;
			}
			node = next;
		}
	}
}