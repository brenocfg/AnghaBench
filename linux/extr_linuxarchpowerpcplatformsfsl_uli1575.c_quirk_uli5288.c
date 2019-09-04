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
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int PCI_CLASS_STORAGE_SATA_AHCI ; 
 int /*<<< orphan*/  is_quirk_valid () ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void quirk_uli5288(struct pci_dev *dev)
{
	unsigned char c;
	unsigned int d;

	if (!is_quirk_valid())
		return;

	/* read/write lock */
	pci_read_config_byte(dev, 0x83, &c);
	pci_write_config_byte(dev, 0x83, c|0x80);

	pci_read_config_dword(dev, PCI_CLASS_REVISION, &d);
	d = (d & 0xff) | (PCI_CLASS_STORAGE_SATA_AHCI << 8);
	pci_write_config_dword(dev, PCI_CLASS_REVISION, d);

	/* restore lock */
	pci_write_config_byte(dev, 0x83, c);

	/* disable emulated PATA mode enabled */
	pci_read_config_byte(dev, 0x84, &c);
	pci_write_config_byte(dev, 0x84, c & ~0x01);
}