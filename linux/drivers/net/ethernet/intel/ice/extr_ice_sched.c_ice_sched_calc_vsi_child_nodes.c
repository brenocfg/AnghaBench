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
typedef  int u16 ;
struct ice_hw {int /*<<< orphan*/ * max_children; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 size_t ice_sched_get_qgrp_layer (struct ice_hw*) ; 
 size_t ice_sched_get_vsi_layer (struct ice_hw*) ; 

__attribute__((used)) static void
ice_sched_calc_vsi_child_nodes(struct ice_hw *hw, u16 num_qs, u16 *num_nodes)
{
	u16 num = num_qs;
	u8 i, qgl, vsil;

	qgl = ice_sched_get_qgrp_layer(hw);
	vsil = ice_sched_get_vsi_layer(hw);

	/* calculate num nodes from queue group to VSI layer */
	for (i = qgl; i > vsil; i--) {
		/* round to the next integer if there is a remainder */
		num = DIV_ROUND_UP(num, hw->max_children[i]);

		/* need at least one node */
		num_nodes[i] = num ? num : 1;
	}
}