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
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_SWFW_SYNC ; 
 int /*<<< orphan*/  IXGBE_GSSR ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ixgbe_get_eeprom_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_release_eeprom_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

s32 ixgbe_acquire_swfw_sync(struct ixgbe_hw *hw, u32 mask)
{
	u32 gssr = 0;
	u32 swmask = mask;
	u32 fwmask = mask << 5;
	u32 timeout = 200;
	u32 i;

	for (i = 0; i < timeout; i++) {
		/*
		 * SW NVM semaphore bit is used for access to all
		 * SW_FW_SYNC bits (not just NVM)
		 */
		if (ixgbe_get_eeprom_semaphore(hw))
			return IXGBE_ERR_SWFW_SYNC;

		gssr = IXGBE_READ_REG(hw, IXGBE_GSSR);
		if (!(gssr & (fwmask | swmask))) {
			gssr |= swmask;
			IXGBE_WRITE_REG(hw, IXGBE_GSSR, gssr);
			ixgbe_release_eeprom_semaphore(hw);
			return 0;
		} else {
			/* Resource is currently in use by FW or SW */
			ixgbe_release_eeprom_semaphore(hw);
			usleep_range(5000, 10000);
		}
	}

	/* If time expired clear the bits holding the lock and retry */
	if (gssr & (fwmask | swmask))
		ixgbe_release_swfw_sync(hw, gssr & (fwmask | swmask));

	usleep_range(5000, 10000);
	return IXGBE_ERR_SWFW_SYNC;
}