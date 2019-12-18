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
typedef  size_t u16 ;
struct TYPE_3__ {scalar_t__ elem_type; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct ice_sched_node {size_t num_children; scalar_t__ tx_sched_layer; struct ice_sched_node** children; TYPE_2__ info; } ;

/* Variables and functions */
 scalar_t__ ICE_AQC_ELEM_TYPE_LEAF ; 
 scalar_t__ ICE_AQC_TOPO_MAX_LEVEL_NUM ; 
 int /*<<< orphan*/  ICE_TXSCHED_GET_NODE_TEID (struct ice_sched_node*) ; 

struct ice_sched_node *
ice_sched_find_node_by_teid(struct ice_sched_node *start_node, u32 teid)
{
	u16 i;

	/* The TEID is same as that of the start_node */
	if (ICE_TXSCHED_GET_NODE_TEID(start_node) == teid)
		return start_node;

	/* The node has no children or is at the max layer */
	if (!start_node->num_children ||
	    start_node->tx_sched_layer >= ICE_AQC_TOPO_MAX_LEVEL_NUM ||
	    start_node->info.data.elem_type == ICE_AQC_ELEM_TYPE_LEAF)
		return NULL;

	/* Check if TEID matches to any of the children nodes */
	for (i = 0; i < start_node->num_children; i++)
		if (ICE_TXSCHED_GET_NODE_TEID(start_node->children[i]) == teid)
			return start_node->children[i];

	/* Search within each child's sub-tree */
	for (i = 0; i < start_node->num_children; i++) {
		struct ice_sched_node *tmp;

		tmp = ice_sched_find_node_by_teid(start_node->children[i],
						  teid);
		if (tmp)
			return tmp;
	}

	return NULL;
}