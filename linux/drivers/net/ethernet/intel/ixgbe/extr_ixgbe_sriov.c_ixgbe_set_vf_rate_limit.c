#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct ixgbe_ring_feature {int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int type; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {int vf_rate_link_speed; TYPE_1__* vfinfo; struct ixgbe_hw hw; struct ixgbe_ring_feature* ring_feature; } ;
struct TYPE_3__ {int tx_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_RTTBCNRC ; 
 int IXGBE_RTTBCNRC_RF_DEC_MASK ; 
 int IXGBE_RTTBCNRC_RF_INT_MASK ; 
 int IXGBE_RTTBCNRC_RF_INT_SHIFT ; 
 int IXGBE_RTTBCNRC_RS_ENA ; 
 int /*<<< orphan*/  IXGBE_RTTBCNRM ; 
 int /*<<< orphan*/  IXGBE_RTTDQSEL ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 size_t RING_F_VMDQ ; 
 int __ALIGN_MASK (int,int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 

__attribute__((used)) static void ixgbe_set_vf_rate_limit(struct ixgbe_adapter *adapter, int vf)
{
	struct ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	struct ixgbe_hw *hw = &adapter->hw;
	u32 bcnrc_val = 0;
	u16 queue, queues_per_pool;
	u16 tx_rate = adapter->vfinfo[vf].tx_rate;

	if (tx_rate) {
		/* start with base link speed value */
		bcnrc_val = adapter->vf_rate_link_speed;

		/* Calculate the rate factor values to set */
		bcnrc_val <<= IXGBE_RTTBCNRC_RF_INT_SHIFT;
		bcnrc_val /= tx_rate;

		/* clear everything but the rate factor */
		bcnrc_val &= IXGBE_RTTBCNRC_RF_INT_MASK |
			     IXGBE_RTTBCNRC_RF_DEC_MASK;

		/* enable the rate scheduler */
		bcnrc_val |= IXGBE_RTTBCNRC_RS_ENA;
	}

	/*
	 * Set global transmit compensation time to the MMW_SIZE in RTTBCNRM
	 * register. Typically MMW_SIZE=0x014 if 9728-byte jumbo is supported
	 * and 0x004 otherwise.
	 */
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
		IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRM, 0x4);
		break;
	case ixgbe_mac_X540:
		IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRM, 0x14);
		break;
	default:
		break;
	}

	/* determine how many queues per pool based on VMDq mask */
	queues_per_pool = __ALIGN_MASK(1, ~vmdq->mask);

	/* write value for all Tx queues belonging to VF */
	for (queue = 0; queue < queues_per_pool; queue++) {
		unsigned int reg_idx = (vf * queues_per_pool) + queue;

		IXGBE_WRITE_REG(hw, IXGBE_RTTDQSEL, reg_idx);
		IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRC, bcnrc_val);
	}
}