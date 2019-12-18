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
struct iavf_hw {int dummy; } ;
struct iavf_adapter {struct iavf_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_VFINT_DYN_CTL01 ; 
 int IAVF_VFINT_DYN_CTL01_INTENA_MASK ; 
 int IAVF_VFINT_DYN_CTL01_ITR_INDX_MASK ; 
 int /*<<< orphan*/  IAVF_VFINT_ICR0_ENA1 ; 
 int IAVF_VFINT_ICR0_ENA1_ADMINQ_MASK ; 
 int /*<<< orphan*/  iavf_flush (struct iavf_hw*) ; 
 int /*<<< orphan*/  wr32 (struct iavf_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iavf_misc_irq_enable(struct iavf_adapter *adapter)
{
	struct iavf_hw *hw = &adapter->hw;

	wr32(hw, IAVF_VFINT_DYN_CTL01, IAVF_VFINT_DYN_CTL01_INTENA_MASK |
				       IAVF_VFINT_DYN_CTL01_ITR_INDX_MASK);
	wr32(hw, IAVF_VFINT_ICR0_ENA1, IAVF_VFINT_ICR0_ENA1_ADMINQ_MASK);

	iavf_flush(hw);
}