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
struct ice_hw {int /*<<< orphan*/  adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_aq_clear_pxe_mode (struct ice_hw*) ; 
 scalar_t__ ice_check_sq_alive (struct ice_hw*,int /*<<< orphan*/ *) ; 

void ice_clear_pxe_mode(struct ice_hw *hw)
{
	if (ice_check_sq_alive(hw, &hw->adminq))
		ice_aq_clear_pxe_mode(hw);
}