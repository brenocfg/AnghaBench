#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int /*<<< orphan*/  semaphore_delay; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_2__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  phy_semaphore_mask; } ;
struct ixgbe_hw {TYPE_4__ eeprom; TYPE_3__ mac; TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CS4227_CHECK_DELAY ; 
 scalar_t__ IXGBE_CS4227_RESET_COMPLETE ; 
 scalar_t__ IXGBE_CS4227_RESET_PENDING ; 
 scalar_t__ IXGBE_CS4227_RETRIES ; 
 int /*<<< orphan*/  IXGBE_CS4227_SCRATCH ; 
 int /*<<< orphan*/  hw_err (struct ixgbe_hw*,char*,scalar_t__) ; 
 scalar_t__ ixgbe_read_cs4227 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ ixgbe_reset_cs4227 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_write_cs4227 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ixgbe_check_cs4227(struct ixgbe_hw *hw)
{
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	s32 status;
	u16 value;
	u8 retry;

	for (retry = 0; retry < IXGBE_CS4227_RETRIES; retry++) {
		status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
		if (status) {
			hw_err(hw, "semaphore failed with %d\n", status);
			msleep(IXGBE_CS4227_CHECK_DELAY);
			continue;
		}

		/* Get status of reset flow. */
		status = ixgbe_read_cs4227(hw, IXGBE_CS4227_SCRATCH, &value);
		if (!status && value == IXGBE_CS4227_RESET_COMPLETE)
			goto out;

		if (status || value != IXGBE_CS4227_RESET_PENDING)
			break;

		/* Reset is pending. Wait and check again. */
		hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		msleep(IXGBE_CS4227_CHECK_DELAY);
	}
	/* If still pending, assume other instance failed. */
	if (retry == IXGBE_CS4227_RETRIES) {
		status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
		if (status) {
			hw_err(hw, "semaphore failed with %d\n", status);
			return;
		}
	}

	/* Reset the CS4227. */
	status = ixgbe_reset_cs4227(hw);
	if (status) {
		hw_err(hw, "CS4227 reset failed: %d", status);
		goto out;
	}

	/* Reset takes so long, temporarily release semaphore in case the
	 * other driver instance is waiting for the reset indication.
	 */
	ixgbe_write_cs4227(hw, IXGBE_CS4227_SCRATCH,
			   IXGBE_CS4227_RESET_PENDING);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	usleep_range(10000, 12000);
	status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
	if (status) {
		hw_err(hw, "semaphore failed with %d", status);
		return;
	}

	/* Record completion for next time. */
	status = ixgbe_write_cs4227(hw, IXGBE_CS4227_SCRATCH,
				    IXGBE_CS4227_RESET_COMPLETE);

out:
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	msleep(hw->eeprom.semaphore_delay);
}