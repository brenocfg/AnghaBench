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
struct i40e_hw {int dummy; } ;
struct i40evf_adapter {int num_msix_vectors; struct i40e_hw hw; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  I40E_VFINT_DYN_CTLN1 (int) ; 
 int I40E_VFINT_DYN_CTLN1_INTENA_MASK ; 
 int I40E_VFINT_DYN_CTLN1_ITR_INDX_MASK ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

void i40evf_irq_enable_queues(struct i40evf_adapter *adapter, u32 mask)
{
	struct i40e_hw *hw = &adapter->hw;
	int i;

	for (i = 1; i < adapter->num_msix_vectors; i++) {
		if (mask & BIT(i - 1)) {
			wr32(hw, I40E_VFINT_DYN_CTLN1(i - 1),
			     I40E_VFINT_DYN_CTLN1_INTENA_MASK |
			     I40E_VFINT_DYN_CTLN1_ITR_INDX_MASK);
		}
	}
}