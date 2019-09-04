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
typedef  scalar_t__ u32 ;
struct ixgbevf_ring {scalar_t__ count; int /*<<< orphan*/  reg_idx; int /*<<< orphan*/  netdev; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VFTDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VFTDT (int /*<<< orphan*/ ) ; 
 struct ixgbevf_adapter* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ixgbevf_get_tx_pending(struct ixgbevf_ring *ring)
{
	struct ixgbevf_adapter *adapter = netdev_priv(ring->netdev);
	struct ixgbe_hw *hw = &adapter->hw;

	u32 head = IXGBE_READ_REG(hw, IXGBE_VFTDH(ring->reg_idx));
	u32 tail = IXGBE_READ_REG(hw, IXGBE_VFTDT(ring->reg_idx));

	if (head != tail)
		return (head < tail) ?
			tail - head : (tail + ring->count - head);

	return 0;
}