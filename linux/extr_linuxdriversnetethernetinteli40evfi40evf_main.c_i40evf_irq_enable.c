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
struct i40e_hw {int dummy; } ;
struct i40evf_adapter {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFGEN_RSTAT ; 
 int /*<<< orphan*/  i40evf_irq_enable_queues (struct i40evf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_misc_irq_enable (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

void i40evf_irq_enable(struct i40evf_adapter *adapter, bool flush)
{
	struct i40e_hw *hw = &adapter->hw;

	i40evf_misc_irq_enable(adapter);
	i40evf_irq_enable_queues(adapter, ~0);

	if (flush)
		rd32(hw, I40E_VFGEN_RSTAT);
}