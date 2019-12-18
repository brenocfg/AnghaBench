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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ e1000_phy_reset (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_copper_link_rtl_setup(struct e1000_hw *hw)
{
	s32 ret_val;

	/* SW reset the PHY so all changes take effect */
	ret_val = e1000_phy_reset(hw);
	if (ret_val) {
		e_dbg("Error Resetting the PHY\n");
		return ret_val;
	}

	return E1000_SUCCESS;
}