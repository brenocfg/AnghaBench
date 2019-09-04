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
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct e1000_adapter {int eiac_mask; scalar_t__ msix_entries; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_EIAC_MASK_82574 ; 
 int E1000_IMS_ECCER ; 
 int E1000_IMS_OTHER ; 
 int /*<<< orphan*/  EIAC_82574 ; 
 int /*<<< orphan*/  IMS ; 
 int IMS_ENABLE_MASK ; 
 int IMS_OTHER_MASK ; 
 scalar_t__ e1000_pch_lpt ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_irq_enable(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	if (adapter->msix_entries) {
		ew32(EIAC_82574, adapter->eiac_mask & E1000_EIAC_MASK_82574);
		ew32(IMS, adapter->eiac_mask | E1000_IMS_OTHER |
		     IMS_OTHER_MASK);
	} else if (hw->mac.type >= e1000_pch_lpt) {
		ew32(IMS, IMS_ENABLE_MASK | E1000_IMS_ECCER);
	} else {
		ew32(IMS, IMS_ENABLE_MASK);
	}
	e1e_flush();
}