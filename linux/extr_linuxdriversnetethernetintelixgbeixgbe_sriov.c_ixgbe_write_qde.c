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
struct ixgbe_ring_feature {int /*<<< orphan*/  mask; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_ring_feature* ring_feature; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_QDE ; 
 int IXGBE_QDE_IDX_SHIFT ; 
 int IXGBE_QDE_WRITE ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 size_t RING_F_VMDQ ; 
 int __ALIGN_MASK (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ixgbe_write_qde(struct ixgbe_adapter *adapter, u32 vf,
				   u32 qde)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	u32 q_per_pool = __ALIGN_MASK(1, ~vmdq->mask);
	int i;

	for (i = vf * q_per_pool; i < ((vf + 1) * q_per_pool); i++) {
		u32 reg;

		/* flush previous write */
		IXGBE_WRITE_FLUSH(hw);

		/* indicate to hardware that we want to set drop enable */
		reg = IXGBE_QDE_WRITE | qde;
		reg |= i <<  IXGBE_QDE_IDX_SHIFT;
		IXGBE_WRITE_REG(hw, IXGBE_QDE, reg);
	}
}