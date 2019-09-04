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
 int PCI_COMMAND ; 
 unsigned short PCI_COMMAND_INTX_DISABLE ; 
 unsigned short PCI_COMMAND_IO ; 
 unsigned short PCI_COMMAND_MASTER ; 
 int /*<<< orphan*/  is_quirk_valid () ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,unsigned short*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,unsigned short) ; 

__attribute__((used)) static void quirk_uli5229(struct pci_dev *dev)
{
	unsigned short temp;

	if (!is_quirk_valid())
		return;

	pci_write_config_word(dev, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE |
		PCI_COMMAND_MASTER | PCI_COMMAND_IO);

	/* Enable Native IRQ 14/15 */
	pci_read_config_word(dev, 0x4a, &temp);
	pci_write_config_word(dev, 0x4a, temp | 0x1000);
}