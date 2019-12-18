#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ elem_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  node_teid; TYPE_2__ data; } ;
struct ice_sched_node {int /*<<< orphan*/  parent; TYPE_1__ info; struct ice_sched_node** children; int /*<<< orphan*/  num_children; } ;
struct ice_port_info {int /*<<< orphan*/  hw; struct ice_sched_node* root; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 scalar_t__ ICE_AQC_ELEM_TYPE_LEAF ; 
 int /*<<< orphan*/  ice_free_sched_node (struct ice_port_info*,struct ice_sched_node*) ; 
 int ice_sched_remove_elems (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_rm_dflt_leaf_node(struct ice_port_info *pi)
{
	struct ice_sched_node *node;

	node = pi->root;
	while (node) {
		if (!node->num_children)
			break;
		node = node->children[0];
	}
	if (node && node->info.data.elem_type == ICE_AQC_ELEM_TYPE_LEAF) {
		u32 teid = le32_to_cpu(node->info.node_teid);
		enum ice_status status;

		/* remove the default leaf node */
		status = ice_sched_remove_elems(pi->hw, node->parent, 1, &teid);
		if (!status)
			ice_free_sched_node(pi, node);
	}
}