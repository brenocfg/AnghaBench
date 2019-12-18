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
struct net_device {int /*<<< orphan*/  name; } ;
struct e1000_adapter {int flags; TYPE_1__* pdev; int /*<<< orphan*/  int_mode; scalar_t__ msix_entries; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000E_INT_MODE_LEGACY ; 
 int /*<<< orphan*/  E1000E_INT_MODE_MSI ; 
 int FLAG_MSI_ENABLED ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  e1000_intr ; 
 int /*<<< orphan*/  e1000_intr_msi ; 
 int e1000_request_msix (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_reset_interrupt_capability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_set_interrupt_capability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e_err (char*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int e1000_request_irq(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err;

	if (adapter->msix_entries) {
		err = e1000_request_msix(adapter);
		if (!err)
			return err;
		/* fall back to MSI */
		e1000e_reset_interrupt_capability(adapter);
		adapter->int_mode = E1000E_INT_MODE_MSI;
		e1000e_set_interrupt_capability(adapter);
	}
	if (adapter->flags & FLAG_MSI_ENABLED) {
		err = request_irq(adapter->pdev->irq, e1000_intr_msi, 0,
				  netdev->name, netdev);
		if (!err)
			return err;

		/* fall back to legacy interrupt */
		e1000e_reset_interrupt_capability(adapter);
		adapter->int_mode = E1000E_INT_MODE_LEGACY;
	}

	err = request_irq(adapter->pdev->irq, e1000_intr, IRQF_SHARED,
			  netdev->name, netdev);
	if (err)
		e_err("Unable to allocate interrupt, Error: %d\n", err);

	return err;
}