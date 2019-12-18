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
typedef  size_t u8 ;
struct TYPE_3__ {scalar_t__ elem_type; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct ice_sched_node {size_t num_children; TYPE_2__ info; struct ice_sched_node** children; } ;

/* Variables and functions */
 scalar_t__ ICE_AQC_ELEM_TYPE_LEAF ; 

__attribute__((used)) static bool ice_sched_is_leaf_node_present(struct ice_sched_node *node)
{
	u8 i;

	for (i = 0; i < node->num_children; i++)
		if (ice_sched_is_leaf_node_present(node->children[i]))
			return true;
	/* check for a leaf node */
	return (node->info.data.elem_type == ICE_AQC_ELEM_TYPE_LEAF);
}