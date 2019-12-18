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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int valid_functions; } ;
struct TYPE_4__ {TYPE_1__ common_cap; } ;
struct ice_hw {TYPE_2__ dev_caps; } ;

/* Variables and functions */
 int ICE_CAPS_VALID_FUNCS_M ; 
 int hweight8 (int) ; 

__attribute__((used)) static u32 ice_get_num_per_func(struct ice_hw *hw, u32 max)
{
	u8 funcs;

#define ICE_CAPS_VALID_FUNCS_M	0xFF
	funcs = hweight8(hw->dev_caps.common_cap.valid_functions &
			 ICE_CAPS_VALID_FUNCS_M);

	if (!funcs)
		return 0;

	return max / funcs;
}