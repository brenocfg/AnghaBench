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
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ ixgbe_start_hw_gen2 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_start_hw_generic (struct ixgbe_hw*) ; 

s32 ixgbe_start_hw_X540(struct ixgbe_hw *hw)
{
	s32 ret_val;

	ret_val = ixgbe_start_hw_generic(hw);
	if (ret_val)
		return ret_val;

	return ixgbe_start_hw_gen2(hw);
}