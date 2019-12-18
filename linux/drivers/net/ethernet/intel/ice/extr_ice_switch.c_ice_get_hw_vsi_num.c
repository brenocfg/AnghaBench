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
typedef  size_t u16 ;
struct ice_hw {TYPE_1__** vsi_ctx; } ;
struct TYPE_2__ {size_t vsi_num; } ;

/* Variables and functions */

u16 ice_get_hw_vsi_num(struct ice_hw *hw, u16 vsi_handle)
{
	return hw->vsi_ctx[vsi_handle]->vsi_num;
}