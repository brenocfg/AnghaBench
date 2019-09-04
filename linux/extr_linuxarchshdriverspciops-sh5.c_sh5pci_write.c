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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CMD (struct pci_bus*,unsigned int,int) ; 
 int /*<<< orphan*/  PAR ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PDR ; 
 int /*<<< orphan*/  SH5PCI_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH5PCI_WRITE_BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH5PCI_WRITE_SHORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh5pci_write(struct pci_bus *bus, unsigned int devfn, int where,
			 int size, u32 val)
{
	SH5PCI_WRITE(PAR, CONFIG_CMD(bus, devfn, where));

	switch (size) {
		case 1:
			SH5PCI_WRITE_BYTE(PDR + (where & 3), (u8)val);
			break;
		case 2:
			SH5PCI_WRITE_SHORT(PDR + (where & 2), (u16)val);
			break;
		case 4:
			SH5PCI_WRITE(PDR, val);
			break;
	}

	return PCIBIOS_SUCCESSFUL;
}