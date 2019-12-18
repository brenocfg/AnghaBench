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
 int /*<<< orphan*/  iavf_flush (struct iavf_hw*) ; 
 int /*<<< orphan*/  iavf_irq_enable_queues (struct iavf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_misc_irq_enable (struct iavf_adapter*) ; 

void iavf_irq_enable(struct iavf_adapter *adapter, bool flush)
{
	struct iavf_hw *hw = &adapter->hw;

	iavf_misc_irq_enable(adapter);
	iavf_irq_enable_queues(adapter, ~0);

	if (flush)
		iavf_flush(hw);
}