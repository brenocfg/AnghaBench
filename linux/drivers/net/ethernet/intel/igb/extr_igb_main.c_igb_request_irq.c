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
struct igb_adapter {int flags; int /*<<< orphan*/ * q_vector; struct pci_dev* pdev; struct net_device* netdev; } ;

/* Variables and functions */
 int IGB_FLAG_HAS_MSI ; 
 int IGB_FLAG_HAS_MSIX ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  igb_assign_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_clear_interrupt_scheme (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_configure (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_all_rx_resources (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_all_tx_resources (struct igb_adapter*) ; 
 int igb_init_interrupt_scheme (struct igb_adapter*,int) ; 
 int /*<<< orphan*/  igb_intr ; 
 int /*<<< orphan*/  igb_intr_msi ; 
 int igb_request_msix (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_reset_interrupt_capability (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_setup_all_rx_resources (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_setup_all_tx_resources (struct igb_adapter*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct igb_adapter*) ; 

__attribute__((used)) static int igb_request_irq(struct igb_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	int err = 0;

	if (adapter->flags & IGB_FLAG_HAS_MSIX) {
		err = igb_request_msix(adapter);
		if (!err)
			goto request_done;
		/* fall back to MSI */
		igb_free_all_tx_resources(adapter);
		igb_free_all_rx_resources(adapter);

		igb_clear_interrupt_scheme(adapter);
		err = igb_init_interrupt_scheme(adapter, false);
		if (err)
			goto request_done;

		igb_setup_all_tx_resources(adapter);
		igb_setup_all_rx_resources(adapter);
		igb_configure(adapter);
	}

	igb_assign_vector(adapter->q_vector[0], 0);

	if (adapter->flags & IGB_FLAG_HAS_MSI) {
		err = request_irq(pdev->irq, igb_intr_msi, 0,
				  netdev->name, adapter);
		if (!err)
			goto request_done;

		/* fall back to legacy interrupts */
		igb_reset_interrupt_capability(adapter);
		adapter->flags &= ~IGB_FLAG_HAS_MSI;
	}

	err = request_irq(pdev->irq, igb_intr, IRQF_SHARED,
			  netdev->name, adapter);

	if (err)
		dev_err(&pdev->dev, "Error %d getting interrupt\n",
			err);

request_done:
	return err;
}