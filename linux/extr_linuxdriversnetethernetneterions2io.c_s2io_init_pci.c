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
struct s2io_nic {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIX_COMMAND_REGISTER ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_PARITY ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s2io_init_pci(struct s2io_nic *sp)
{
	u16 pci_cmd = 0, pcix_cmd = 0;

	/* Enable Data Parity Error Recovery in PCI-X command register. */
	pci_read_config_word(sp->pdev, PCIX_COMMAND_REGISTER,
			     &(pcix_cmd));
	pci_write_config_word(sp->pdev, PCIX_COMMAND_REGISTER,
			      (pcix_cmd | 1));
	pci_read_config_word(sp->pdev, PCIX_COMMAND_REGISTER,
			     &(pcix_cmd));

	/* Set the PErr Response bit in PCI command register. */
	pci_read_config_word(sp->pdev, PCI_COMMAND, &pci_cmd);
	pci_write_config_word(sp->pdev, PCI_COMMAND,
			      (pci_cmd | PCI_COMMAND_PARITY));
	pci_read_config_word(sp->pdev, PCI_COMMAND, &pci_cmd);
}