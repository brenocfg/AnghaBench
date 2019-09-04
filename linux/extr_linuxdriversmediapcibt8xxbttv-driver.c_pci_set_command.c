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
struct pci_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void pci_set_command(struct pci_dev *dev)
{
#if defined(__powerpc__)
	unsigned int cmd;

	pci_read_config_dword(dev, PCI_COMMAND, &cmd);
	cmd = (cmd | PCI_COMMAND_MEMORY );
	pci_write_config_dword(dev, PCI_COMMAND, cmd);
#endif
}