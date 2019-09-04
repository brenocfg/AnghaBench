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
struct ice_port_info {struct ice_hw* hw; } ;
struct ice_hw {size_t sw_entry_point_layer; TYPE_1__* layer_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  max_pf_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int ICE_ERR_CFG ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ ice_sched_get_num_nodes_per_layer (struct ice_port_info*,size_t) ; 
 size_t ice_sched_get_qgrp_layer (struct ice_hw*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_sched_validate_for_max_nodes(struct ice_port_info *pi,
				 u16 *new_num_nodes_per_layer)
{
	struct ice_hw *hw = pi->hw;
	u8 i, qg_layer;
	u16 num_nodes;

	qg_layer = ice_sched_get_qgrp_layer(hw);

	/* walk through all the layers from SW entry point to qgroup layer */
	for (i = hw->sw_entry_point_layer; i <= qg_layer; i++) {
		num_nodes = ice_sched_get_num_nodes_per_layer(pi, i);
		if (num_nodes + new_num_nodes_per_layer[i] >
		    le16_to_cpu(hw->layer_info[i].max_pf_nodes)) {
			ice_debug(hw, ICE_DBG_SCHED,
				  "max nodes reached for layer = %d\n", i);
			return ICE_ERR_CFG;
		}
	}
	return 0;
}