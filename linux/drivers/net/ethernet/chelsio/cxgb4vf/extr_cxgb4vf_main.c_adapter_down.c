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
struct adapter {int flags; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int CXGB4VF_USING_MSIX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adapter*) ; 
 int /*<<< orphan*/  free_msix_queue_irqs (struct adapter*) ; 
 int /*<<< orphan*/  quiesce_rx (struct adapter*) ; 

__attribute__((used)) static void adapter_down(struct adapter *adapter)
{
	/*
	 * Free interrupt resources.
	 */
	if (adapter->flags & CXGB4VF_USING_MSIX)
		free_msix_queue_irqs(adapter);
	else
		free_irq(adapter->pdev->irq, adapter);

	/*
	 * Wait for NAPI handlers to finish.
	 */
	quiesce_rx(adapter);
}