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
struct igc_hw {int dummy; } ;
struct igc_adapter {int eims_enable_mask; scalar_t__ msix_entries; struct igc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_EIAC ; 
 int /*<<< orphan*/  IGC_EIAM ; 
 int /*<<< orphan*/  IGC_EIMS ; 
 int /*<<< orphan*/  IGC_IAM ; 
 int /*<<< orphan*/  IGC_IMS ; 
 int IGC_IMS_DOUTSYNC ; 
 int IGC_IMS_DRSTA ; 
 int IGC_IMS_LSC ; 
 int IMS_ENABLE_MASK ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igc_irq_enable(struct igc_adapter *adapter)
{
	struct igc_hw *hw = &adapter->hw;

	if (adapter->msix_entries) {
		u32 ims = IGC_IMS_LSC | IGC_IMS_DOUTSYNC | IGC_IMS_DRSTA;
		u32 regval = rd32(IGC_EIAC);

		wr32(IGC_EIAC, regval | adapter->eims_enable_mask);
		regval = rd32(IGC_EIAM);
		wr32(IGC_EIAM, regval | adapter->eims_enable_mask);
		wr32(IGC_EIMS, adapter->eims_enable_mask);
		wr32(IGC_IMS, ims);
	} else {
		wr32(IGC_IMS, IMS_ENABLE_MASK | IGC_IMS_DRSTA);
		wr32(IGC_IAM, IMS_ENABLE_MASK | IGC_IMS_DRSTA);
	}
}