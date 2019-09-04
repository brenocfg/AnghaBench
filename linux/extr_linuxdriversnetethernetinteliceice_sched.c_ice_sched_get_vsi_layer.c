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
struct ice_hw {scalar_t__ num_tx_sched_layers; scalar_t__ sw_entry_point_layer; } ;

/* Variables and functions */
 scalar_t__ ICE_VSI_LAYER_OFFSET ; 

__attribute__((used)) static u8 ice_sched_get_vsi_layer(struct ice_hw *hw)
{
	/* Num Layers       VSI layer
	 *     9               6
	 *     7               4
	 *     5 or less       sw_entry_point_layer
	 */
	/* calculate the vsi layer based on number of layers. */
	if (hw->num_tx_sched_layers > ICE_VSI_LAYER_OFFSET + 1) {
		u8 layer = hw->num_tx_sched_layers - ICE_VSI_LAYER_OFFSET;

		if (layer > hw->sw_entry_point_layer)
			return layer;
	}
	return hw->sw_entry_point_layer;
}