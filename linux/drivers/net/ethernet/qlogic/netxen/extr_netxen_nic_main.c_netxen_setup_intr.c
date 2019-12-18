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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct netxen_adapter {int max_sds_rings; int flags; TYPE_1__* msix_entries; scalar_t__ rss_supported; struct pci_dev* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ MSIX_ENTRIES_PER_ADAPTER ; 
 scalar_t__ NETXEN_INTX_MODE ; 
 int /*<<< orphan*/  NETXEN_IS_MSI_FAMILY (struct netxen_adapter*) ; 
 scalar_t__ NETXEN_MSI_MODE ; 
 int NETXEN_NIC_MSIX_ENABLED ; 
 int NETXEN_NIC_MSI_ENABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ netxen_function_zero (struct pci_dev*) ; 
 scalar_t__ netxen_get_interrupt_mode (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_initialize_interrupt_registers (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_set_interrupt_mode (struct netxen_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  netxen_set_msix_bit (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ netxen_setup_msi_interrupts (struct netxen_adapter*,int) ; 
 scalar_t__ num_online_cpus () ; 

__attribute__((used)) static int netxen_setup_intr(struct netxen_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	int num_msix;

	if (adapter->rss_supported)
		num_msix = (num_online_cpus() >= MSIX_ENTRIES_PER_ADAPTER) ?
			    MSIX_ENTRIES_PER_ADAPTER : 2;
	else
		num_msix = 1;

	adapter->max_sds_rings = 1;
	adapter->flags &= ~(NETXEN_NIC_MSI_ENABLED | NETXEN_NIC_MSIX_ENABLED);

	netxen_initialize_interrupt_registers(adapter);
	netxen_set_msix_bit(pdev, 0);

	if (netxen_function_zero(pdev)) {
		if (!netxen_setup_msi_interrupts(adapter, num_msix))
			netxen_set_interrupt_mode(adapter, NETXEN_MSI_MODE);
		else
			netxen_set_interrupt_mode(adapter, NETXEN_INTX_MODE);
	} else {
		if (netxen_get_interrupt_mode(adapter) == NETXEN_MSI_MODE &&
		    netxen_setup_msi_interrupts(adapter, num_msix)) {
			dev_err(&pdev->dev, "Co-existence of MSI-X/MSI and INTx interrupts is not supported\n");
			return -EIO;
		}
	}

	if (!NETXEN_IS_MSI_FAMILY(adapter)) {
		adapter->msix_entries[0].vector = pdev->irq;
		dev_info(&pdev->dev, "using legacy interrupts\n");
	}
	return 0;
}