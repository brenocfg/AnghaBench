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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct igc_adapter {int flags; int /*<<< orphan*/ * q_vector; struct pci_dev* pdev; struct net_device* netdev; } ;

/* Variables and functions */
 int IGC_FLAG_HAS_MSI ; 
 int IGC_FLAG_HAS_MSIX ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  igc_assign_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igc_clear_interrupt_scheme (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_configure (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_all_rx_resources (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_all_tx_resources (struct igc_adapter*) ; 
 int igc_init_interrupt_scheme (struct igc_adapter*,int) ; 
 int /*<<< orphan*/  igc_intr ; 
 int /*<<< orphan*/  igc_intr_msi ; 
 int igc_request_msix (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_reset_interrupt_capability (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_setup_all_rx_resources (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_setup_all_tx_resources (struct igc_adapter*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct igc_adapter*) ; 

__attribute__((used)) static int igc_request_irq(struct igc_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	int err = 0;

	if (adapter->flags & IGC_FLAG_HAS_MSIX) {
		err = igc_request_msix(adapter);
		if (!err)
			goto request_done;
		/* fall back to MSI */
		igc_free_all_tx_resources(adapter);
		igc_free_all_rx_resources(adapter);

		igc_clear_interrupt_scheme(adapter);
		err = igc_init_interrupt_scheme(adapter, false);
		if (err)
			goto request_done;
		igc_setup_all_tx_resources(adapter);
		igc_setup_all_rx_resources(adapter);
		igc_configure(adapter);
	}

	igc_assign_vector(adapter->q_vector[0], 0);

	if (adapter->flags & IGC_FLAG_HAS_MSI) {
		err = request_irq(pdev->irq, &igc_intr_msi, 0,
				  netdev->name, adapter);
		if (!err)
			goto request_done;

		/* fall back to legacy interrupts */
		igc_reset_interrupt_capability(adapter);
		adapter->flags &= ~IGC_FLAG_HAS_MSI;
	}

	err = request_irq(pdev->irq, &igc_intr, IRQF_SHARED,
			  netdev->name, adapter);

	if (err)
		dev_err(&pdev->dev, "Error %d getting interrupt\n",
			err);

request_done:
	return err;
}