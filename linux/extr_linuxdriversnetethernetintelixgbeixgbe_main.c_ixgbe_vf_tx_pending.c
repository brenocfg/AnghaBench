#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ixgbe_ring_feature {int /*<<< orphan*/  mask; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int num_vfs; struct ixgbe_ring_feature* ring_feature; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PVFTDHN (int,int,int) ; 
 int /*<<< orphan*/  IXGBE_PVFTDTN (int,int,int) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 size_t RING_F_VMDQ ; 
 int __ALIGN_MASK (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_X550 ; 

__attribute__((used)) static bool ixgbe_vf_tx_pending(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	u32 q_per_pool = __ALIGN_MASK(1, ~vmdq->mask);

	int i, j;

	if (!adapter->num_vfs)
		return false;

	/* resetting the PF is only needed for MAC before X550 */
	if (hw->mac.type >= ixgbe_mac_X550)
		return false;

	for (i = 0; i < adapter->num_vfs; i++) {
		for (j = 0; j < q_per_pool; j++) {
			u32 h, t;

			h = IXGBE_READ_REG(hw, IXGBE_PVFTDHN(q_per_pool, i, j));
			t = IXGBE_READ_REG(hw, IXGBE_PVFTDTN(q_per_pool, i, j));

			if (h != t)
				return true;
		}
	}

	return false;
}