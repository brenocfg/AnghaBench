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
struct ice_hw {scalar_t__ num_tx_sched_layers; } ;

/* Variables and functions */
 scalar_t__ ICE_QGRP_LAYER_OFFSET ; 

__attribute__((used)) static u8 ice_sched_get_qgrp_layer(struct ice_hw *hw)
{
	/* It's always total layers - 1, the array is 0 relative so -2 */
	return hw->num_tx_sched_layers - ICE_QGRP_LAYER_OFFSET;
}