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
struct e1000_hw {int dummy; } ;
struct igb_adapter {int flags; int eims_enable_mask; scalar_t__ vfs_allocated_count; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EIAC ; 
 int /*<<< orphan*/  E1000_EIAM ; 
 int /*<<< orphan*/  E1000_EIMS ; 
 int /*<<< orphan*/  E1000_IAM ; 
 int /*<<< orphan*/  E1000_IMS ; 
 int E1000_IMS_DOUTSYNC ; 
 int E1000_IMS_DRSTA ; 
 int E1000_IMS_LSC ; 
 int E1000_IMS_VMMB ; 
 int /*<<< orphan*/  E1000_MBVFIMR ; 
 int IGB_FLAG_HAS_MSIX ; 
 int IMS_ENABLE_MASK ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_irq_enable(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	if (adapter->flags & IGB_FLAG_HAS_MSIX) {
		u32 ims = E1000_IMS_LSC | E1000_IMS_DOUTSYNC | E1000_IMS_DRSTA;
		u32 regval = rd32(E1000_EIAC);

		wr32(E1000_EIAC, regval | adapter->eims_enable_mask);
		regval = rd32(E1000_EIAM);
		wr32(E1000_EIAM, regval | adapter->eims_enable_mask);
		wr32(E1000_EIMS, adapter->eims_enable_mask);
		if (adapter->vfs_allocated_count) {
			wr32(E1000_MBVFIMR, 0xFF);
			ims |= E1000_IMS_VMMB;
		}
		wr32(E1000_IMS, ims);
	} else {
		wr32(E1000_IMS, IMS_ENABLE_MASK |
				E1000_IMS_DRSTA);
		wr32(E1000_IAM, IMS_ENABLE_MASK |
				E1000_IMS_DRSTA);
	}
}