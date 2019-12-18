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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int) ;} ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ ops; } ;
struct TYPE_4__ {int phy_semaphore_mask; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_SWFW_SYNC ; 
 int IXGBE_SFP_DETECT_RETRIES ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  ixgbe_clock_in_i2c_byte (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_clock_out_i2c_bit (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_clock_out_i2c_byte (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_get_i2c_ack (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_bus_clear (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_start (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_stop (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_is_sfp_probe (struct ixgbe_hw*,int,int) ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int) ; 

__attribute__((used)) static s32 ixgbe_read_i2c_byte_generic_int(struct ixgbe_hw *hw, u8 byte_offset,
					   u8 dev_addr, u8 *data, bool lock)
{
	s32 status;
	u32 max_retry = 10;
	u32 retry = 0;
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	bool nack = true;

	if (hw->mac.type >= ixgbe_mac_X550)
		max_retry = 3;
	if (ixgbe_is_sfp_probe(hw, byte_offset, dev_addr))
		max_retry = IXGBE_SFP_DETECT_RETRIES;

	*data = 0;

	do {
		if (lock && hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
			return IXGBE_ERR_SWFW_SYNC;

		ixgbe_i2c_start(hw);

		/* Device Address and write indication */
		status = ixgbe_clock_out_i2c_byte(hw, dev_addr);
		if (status != 0)
			goto fail;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto fail;

		status = ixgbe_clock_out_i2c_byte(hw, byte_offset);
		if (status != 0)
			goto fail;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto fail;

		ixgbe_i2c_start(hw);

		/* Device Address and read indication */
		status = ixgbe_clock_out_i2c_byte(hw, (dev_addr | 0x1));
		if (status != 0)
			goto fail;

		status = ixgbe_get_i2c_ack(hw);
		if (status != 0)
			goto fail;

		status = ixgbe_clock_in_i2c_byte(hw, data);
		if (status != 0)
			goto fail;

		status = ixgbe_clock_out_i2c_bit(hw, nack);
		if (status != 0)
			goto fail;

		ixgbe_i2c_stop(hw);
		if (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		return 0;

fail:
		ixgbe_i2c_bus_clear(hw);
		if (lock) {
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
			msleep(100);
		}
		retry++;
		if (retry < max_retry)
			hw_dbg(hw, "I2C byte read error - Retrying.\n");
		else
			hw_dbg(hw, "I2C byte read error.\n");

	} while (retry < max_retry);

	return status;
}