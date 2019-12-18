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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pci_intx_mask_broken(struct pci_dev *dev)
{
	u16 orig, toggle, new;

	pci_read_config_word(dev, PCI_COMMAND, &orig);
	toggle = orig ^ PCI_COMMAND_INTX_DISABLE;
	pci_write_config_word(dev, PCI_COMMAND, toggle);
	pci_read_config_word(dev, PCI_COMMAND, &new);

	pci_write_config_word(dev, PCI_COMMAND, orig);

	/*
	 * PCI_COMMAND_INTX_DISABLE was reserved and read-only prior to PCI
	 * r2.3, so strictly speaking, a device is not *broken* if it's not
	 * writable.  But we'll live with the misnomer for now.
	 */
	if (new != toggle)
		return 1;
	return 0;
}