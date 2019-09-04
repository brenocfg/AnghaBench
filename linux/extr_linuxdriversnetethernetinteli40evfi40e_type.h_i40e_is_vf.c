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
struct TYPE_2__ {scalar_t__ type; } ;
struct i40e_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 scalar_t__ I40E_MAC_VF ; 
 scalar_t__ I40E_MAC_X722_VF ; 

__attribute__((used)) static inline bool i40e_is_vf(struct i40e_hw *hw)
{
	return (hw->mac.type == I40E_MAC_VF ||
		hw->mac.type == I40E_MAC_X722_VF);
}