#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {size_t pci_func; } ;
struct netxen_adapter {int max_sds_rings; TYPE_2__* msix_entries; int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  flags; TYPE_1__ ahw; scalar_t__ rss_supported; scalar_t__ msix_supported; struct pci_dev* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NETXEN_NIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  NETXEN_NIC_MSI_ENABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * msi_tgt_status ; 
 int /*<<< orphan*/  netxen_get_ioaddr (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_init_msix_entries (struct netxen_adapter*,int) ; 
 int /*<<< orphan*/  netxen_set_msix_bit (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int pci_enable_msix_range (struct pci_dev*,TYPE_2__*,int,int) ; 
 scalar_t__ use_msi ; 

__attribute__((used)) static int netxen_setup_msi_interrupts(struct netxen_adapter *adapter,
				       int num_msix)
{
	struct pci_dev *pdev = adapter->pdev;
	u32 value;
	int err;

	if (adapter->msix_supported) {
		netxen_init_msix_entries(adapter, num_msix);
		err = pci_enable_msix_range(pdev, adapter->msix_entries,
					    num_msix, num_msix);
		if (err > 0) {
			adapter->flags |= NETXEN_NIC_MSIX_ENABLED;
			netxen_set_msix_bit(pdev, 1);

			if (adapter->rss_supported)
				adapter->max_sds_rings = num_msix;

			dev_info(&pdev->dev, "using msi-x interrupts\n");
			return 0;
		}
		/* fall through for msi */
	}

	if (use_msi && !pci_enable_msi(pdev)) {
		value = msi_tgt_status[adapter->ahw.pci_func];
		adapter->flags |= NETXEN_NIC_MSI_ENABLED;
		adapter->tgt_status_reg = netxen_get_ioaddr(adapter, value);
		adapter->msix_entries[0].vector = pdev->irq;
		dev_info(&pdev->dev, "using msi interrupts\n");
		return 0;
	}

	dev_err(&pdev->dev, "Failed to acquire MSI-X/MSI interrupt vector\n");
	return -EIO;
}