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
struct igc_hw {int dummy; } ;
struct igc_adapter {int eims_enable_mask; int num_q_vectors; TYPE_2__* pdev; TYPE_1__* msix_entries; struct igc_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_EIAC ; 
 int /*<<< orphan*/  IGC_EIAM ; 
 int /*<<< orphan*/  IGC_EIMC ; 
 int /*<<< orphan*/  IGC_IAM ; 
 int /*<<< orphan*/  IGC_IMC ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igc_irq_disable(struct igc_adapter *adapter)
{
	struct igc_hw *hw = &adapter->hw;

	if (adapter->msix_entries) {
		u32 regval = rd32(IGC_EIAM);

		wr32(IGC_EIAM, regval & ~adapter->eims_enable_mask);
		wr32(IGC_EIMC, adapter->eims_enable_mask);
		regval = rd32(IGC_EIAC);
		wr32(IGC_EIAC, regval & ~adapter->eims_enable_mask);
	}

	wr32(IGC_IAM, 0);
	wr32(IGC_IMC, ~0);
	wrfl();

	if (adapter->msix_entries) {
		int vector = 0, i;

		synchronize_irq(adapter->msix_entries[vector++].vector);

		for (i = 0; i < adapter->num_q_vectors; i++)
			synchronize_irq(adapter->msix_entries[vector++].vector);
	} else {
		synchronize_irq(adapter->pdev->irq);
	}
}