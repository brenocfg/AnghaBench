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
struct i40e_hw {int dummy; } ;
struct i40evf_adapter {TYPE_1__* msix_entries; struct i40e_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFGEN_RSTAT ; 
 int /*<<< orphan*/  I40E_VFINT_DYN_CTL01 ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40evf_misc_irq_disable(struct i40evf_adapter *adapter)
{
	struct i40e_hw *hw = &adapter->hw;

	if (!adapter->msix_entries)
		return;

	wr32(hw, I40E_VFINT_DYN_CTL01, 0);

	/* read flush */
	rd32(hw, I40E_VFGEN_RSTAT);

	synchronize_irq(adapter->msix_entries[0].vector);
}