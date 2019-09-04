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
typedef  int u16 ;
struct ice_hw {TYPE_1__* layer_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_children; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 size_t ice_sched_get_qgrp_layer (struct ice_hw*) ; 
 size_t ice_sched_get_vsi_layer (struct ice_hw*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_sched_calc_vsi_child_nodes(struct ice_hw *hw, u16 num_qs, u16 *num_nodes)
{
	u16 num = num_qs;
	u8 i, qgl, vsil;

	qgl = ice_sched_get_qgrp_layer(hw);
	vsil = ice_sched_get_vsi_layer(hw);

	/* calculate num nodes from q group to VSI layer */
	for (i = qgl; i > vsil; i--) {
		u16 max_children = le16_to_cpu(hw->layer_info[i].max_children);

		/* round to the next integer if there is a remainder */
		num = DIV_ROUND_UP(num, max_children);

		/* need at least one node */
		num_nodes[i] = num ? num : 1;
	}
}