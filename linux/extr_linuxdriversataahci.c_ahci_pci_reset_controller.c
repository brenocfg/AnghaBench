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
typedef  int u16 ;
struct pci_dev {scalar_t__ vendor; } ;
struct ata_host {struct ahci_host_priv* private_data; int /*<<< orphan*/  dev; } ;
struct ahci_host_priv {int port_map; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int ahci_reset_controller (struct ata_host*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahci_pci_reset_controller(struct ata_host *host)
{
	struct pci_dev *pdev = to_pci_dev(host->dev);
	int rc;

	rc = ahci_reset_controller(host);
	if (rc)
		return rc;

	if (pdev->vendor == PCI_VENDOR_ID_INTEL) {
		struct ahci_host_priv *hpriv = host->private_data;
		u16 tmp16;

		/* configure PCS */
		pci_read_config_word(pdev, 0x92, &tmp16);
		if ((tmp16 & hpriv->port_map) != hpriv->port_map) {
			tmp16 |= hpriv->port_map;
			pci_write_config_word(pdev, 0x92, tmp16);
		}
	}

	return 0;
}