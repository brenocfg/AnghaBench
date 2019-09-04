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

/* Variables and functions */
 int IXGBE_GSSR_I2C_MASK ; 
 int IXGBE_GSSR_NVM_PHY_MASK ; 
 int IXGBE_GSSR_SW_MNG_SM ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SWFW_SYNC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_get_swfw_sync_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void ixgbe_release_swfw_sync_X540(struct ixgbe_hw *hw, u32 mask)
{
	u32 swmask = mask & (IXGBE_GSSR_NVM_PHY_MASK | IXGBE_GSSR_SW_MNG_SM);
	u32 swfw_sync;

	if (mask & IXGBE_GSSR_I2C_MASK)
		swmask |= mask & IXGBE_GSSR_I2C_MASK;
	ixgbe_get_swfw_sync_semaphore(hw);

	swfw_sync = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC(hw));
	swfw_sync &= ~swmask;
	IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC(hw), swfw_sync);

	ixgbe_release_swfw_sync_semaphore(hw);
	usleep_range(5000, 6000);
}