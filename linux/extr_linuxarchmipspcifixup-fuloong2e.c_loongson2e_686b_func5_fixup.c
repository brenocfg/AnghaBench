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
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,unsigned int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 

__attribute__((used)) static void loongson2e_686b_func5_fixup(struct pci_dev *pdev)
{
	unsigned int val;
	unsigned char c;

	/* enable IO */
	pci_write_config_byte(pdev, PCI_COMMAND,
			      PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
			      PCI_COMMAND_MASTER);
	pci_read_config_dword(pdev, 0x4, &val);
	pci_write_config_dword(pdev, 0x4, val | 1);

	/* route ac97 IRQ */
	pci_write_config_byte(pdev, 0x3c, 9);

	pci_read_config_byte(pdev, 0x8, &c);

	/* link control: enable link & SGD PCM output */
	pci_write_config_byte(pdev, 0x41, 0xcc);

	/* disable game port, FM, midi, sb, enable write to reg2c-2f */
	pci_write_config_byte(pdev, 0x42, 0x20);

	/* we are using Avance logic codec */
	pci_write_config_word(pdev, 0x2c, 0x1005);
	pci_write_config_word(pdev, 0x2e, 0x4710);
	pci_read_config_dword(pdev, 0x2c, &val);

	pci_write_config_byte(pdev, 0x42, 0x0);
}