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
struct e1000_adapter {int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int FLAG_MSI_ENABLED ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_SERR ; 
 int e1000_test_msi_interrupt (struct e1000_adapter*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int e1000_test_msi(struct e1000_adapter *adapter)
{
	int err;
	u16 pci_cmd;

	if (!(adapter->flags & FLAG_MSI_ENABLED))
		return 0;

	/* disable SERR in case the MSI write causes a master abort */
	pci_read_config_word(adapter->pdev, PCI_COMMAND, &pci_cmd);
	if (pci_cmd & PCI_COMMAND_SERR)
		pci_write_config_word(adapter->pdev, PCI_COMMAND,
				      pci_cmd & ~PCI_COMMAND_SERR);

	err = e1000_test_msi_interrupt(adapter);

	/* re-enable SERR */
	if (pci_cmd & PCI_COMMAND_SERR) {
		pci_read_config_word(adapter->pdev, PCI_COMMAND, &pci_cmd);
		pci_cmd |= PCI_COMMAND_SERR;
		pci_write_config_word(adapter->pdev, PCI_COMMAND, pci_cmd);
	}

	return err;
}