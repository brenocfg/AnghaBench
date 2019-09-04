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
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_BASE1000T_STATUS ; 
 scalar_t__ E1000_IDLE_ERROR_COUNT_MASK ; 
 int /*<<< orphan*/  E1000_RECEIVE_ERROR_COUNTER ; 
 scalar_t__ E1000_RECEIVE_ERROR_MAX ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

bool e1000_check_phy_82574(struct e1000_hw *hw)
{
	u16 status_1kbt = 0;
	u16 receive_errors = 0;
	s32 ret_val;

	/* Read PHY Receive Error counter first, if its is max - all F's then
	 * read the Base1000T status register If both are max then PHY is hung.
	 */
	ret_val = e1e_rphy(hw, E1000_RECEIVE_ERROR_COUNTER, &receive_errors);
	if (ret_val)
		return false;
	if (receive_errors == E1000_RECEIVE_ERROR_MAX) {
		ret_val = e1e_rphy(hw, E1000_BASE1000T_STATUS, &status_1kbt);
		if (ret_val)
			return false;
		if ((status_1kbt & E1000_IDLE_ERROR_COUNT_MASK) ==
		    E1000_IDLE_ERROR_COUNT_MASK)
			return true;
	}

	return false;
}