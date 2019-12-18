#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_semaphore_mask; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_I2C ; 
 int /*<<< orphan*/  IXGBE_ERR_SWFW_SYNC ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_clock_in_i2c_byte (struct ixgbe_hw*,int*) ; 
 scalar_t__ ixgbe_clock_out_i2c_bit (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_i2c_bus_clear (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_start (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_stop (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_in_i2c_byte_ack (struct ixgbe_hw*,int*) ; 
 int ixgbe_ones_comp_byte_add (int,int) ; 
 scalar_t__ ixgbe_out_i2c_byte_ack (struct ixgbe_hw*,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

s32 ixgbe_read_i2c_combined_generic_int(struct ixgbe_hw *hw, u8 addr,
					u16 reg, u16 *val, bool lock)
{
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	int max_retry = 3;
	int retry = 0;
	u8 csum_byte;
	u8 high_bits;
	u8 low_bits;
	u8 reg_high;
	u8 csum;

	reg_high = ((reg >> 7) & 0xFE) | 1;     /* Indicate read combined */
	csum = ixgbe_ones_comp_byte_add(reg_high, reg & 0xFF);
	csum = ~csum;
	do {
		if (lock && hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
			return IXGBE_ERR_SWFW_SYNC;
		ixgbe_i2c_start(hw);
		/* Device Address and write indication */
		if (ixgbe_out_i2c_byte_ack(hw, addr))
			goto fail;
		/* Write bits 14:8 */
		if (ixgbe_out_i2c_byte_ack(hw, reg_high))
			goto fail;
		/* Write bits 7:0 */
		if (ixgbe_out_i2c_byte_ack(hw, reg & 0xFF))
			goto fail;
		/* Write csum */
		if (ixgbe_out_i2c_byte_ack(hw, csum))
			goto fail;
		/* Re-start condition */
		ixgbe_i2c_start(hw);
		/* Device Address and read indication */
		if (ixgbe_out_i2c_byte_ack(hw, addr | 1))
			goto fail;
		/* Get upper bits */
		if (ixgbe_in_i2c_byte_ack(hw, &high_bits))
			goto fail;
		/* Get low bits */
		if (ixgbe_in_i2c_byte_ack(hw, &low_bits))
			goto fail;
		/* Get csum */
		if (ixgbe_clock_in_i2c_byte(hw, &csum_byte))
			goto fail;
		/* NACK */
		if (ixgbe_clock_out_i2c_bit(hw, false))
			goto fail;
		ixgbe_i2c_stop(hw);
		if (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		*val = (high_bits << 8) | low_bits;
		return 0;

fail:
		ixgbe_i2c_bus_clear(hw);
		if (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		retry++;
		if (retry < max_retry)
			hw_dbg(hw, "I2C byte read combined error - Retry.\n");
		else
			hw_dbg(hw, "I2C byte read combined error.\n");
	} while (retry < max_retry);

	return IXGBE_ERR_I2C;
}