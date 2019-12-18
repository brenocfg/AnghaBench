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
struct iavf_hw {int dummy; } ;
struct iavf_adapter {TYPE_1__* msix_entries; struct iavf_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_VFINT_DYN_CTL01 ; 
 int /*<<< orphan*/  iavf_flush (struct iavf_hw*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct iavf_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iavf_misc_irq_disable(struct iavf_adapter *adapter)
{
	struct iavf_hw *hw = &adapter->hw;

	if (!adapter->msix_entries)
		return;

	wr32(hw, IAVF_VFINT_DYN_CTL01, 0);

	iavf_flush(hw);

	synchronize_irq(adapter->msix_entries[0].vector);
}