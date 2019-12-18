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
 scalar_t__ ixgbe_clock_in_i2c_byte (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ ixgbe_clock_out_i2c_bit (struct ixgbe_hw*,int) ; 

__attribute__((used)) static s32 ixgbe_in_i2c_byte_ack(struct ixgbe_hw *hw, u8 *byte)
{
	s32 status;

	status = ixgbe_clock_in_i2c_byte(hw, byte);
	if (status)
		return status;
	/* ACK */
	return ixgbe_clock_out_i2c_bit(hw, false);
}