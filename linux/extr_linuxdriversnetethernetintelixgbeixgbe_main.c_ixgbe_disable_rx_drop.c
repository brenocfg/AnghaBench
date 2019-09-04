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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_ring {int /*<<< orphan*/  reg_idx; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SRRCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SRRCTL_DROP_EN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_disable_rx_drop(struct ixgbe_adapter *adapter,
				  struct ixgbe_ring *ring)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u8 reg_idx = ring->reg_idx;
	u32 srrctl = IXGBE_READ_REG(hw, IXGBE_SRRCTL(reg_idx));

	srrctl &= ~IXGBE_SRRCTL_DROP_EN;

	IXGBE_WRITE_REG(hw, IXGBE_SRRCTL(reg_idx), srrctl);
}