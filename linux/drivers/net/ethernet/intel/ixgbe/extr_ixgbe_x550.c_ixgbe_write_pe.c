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
typedef  int /*<<< orphan*/  u8 ;
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PE ; 
 int /*<<< orphan*/  hw_err (struct ixgbe_hw*,char*,scalar_t__) ; 
 scalar_t__ ixgbe_write_i2c_byte_generic_unlocked (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_write_pe(struct ixgbe_hw *hw, u8 reg, u8 value)
{
	s32 status;

	status = ixgbe_write_i2c_byte_generic_unlocked(hw, reg, IXGBE_PE,
						       value);
	if (status)
		hw_err(hw, "port expander access failed with %d\n", status);
	return status;
}