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
struct igc_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ igc_check_reset_block (struct igc_hw*) ; 
 scalar_t__ igc_enable_mng_pass_thru (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_power_down_phy_copper (struct igc_hw*) ; 

void igc_power_down_phy_copper_base(struct igc_hw *hw)
{
	/* If the management interface is not enabled, then power down */
	if (!(igc_enable_mng_pass_thru(hw) || igc_check_reset_block(hw)))
		igc_power_down_phy_copper(hw);
}