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
typedef  int u32 ;
struct pci_bus {unsigned char number; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSC01_PCI_CFGADDR ; 
 unsigned char MSC01_PCI_CFGADDR_BNUM_SHF ; 
 unsigned char MSC01_PCI_CFGADDR_DNUM_SHF ; 
 unsigned char MSC01_PCI_CFGADDR_FNUM_SHF ; 
 int MSC01_PCI_CFGADDR_RNUM_SHF ; 
 int /*<<< orphan*/  MSC01_PCI_CFGDATA ; 
 int MSC01_PCI_INTCFG_MA_BIT ; 
 int MSC01_PCI_INTCFG_TA_BIT ; 
 int /*<<< orphan*/  MSC01_PCI_INTSTAT ; 
 int /*<<< orphan*/  MSC_READ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSC_WRITE (int /*<<< orphan*/ ,int) ; 
 unsigned char PCI_ACCESS_WRITE ; 
 unsigned char PCI_FUNC (unsigned int) ; 
 unsigned char PCI_SLOT (unsigned int) ; 

__attribute__((used)) static int msc_pcibios_config_access(unsigned char access_type,
	struct pci_bus *bus, unsigned int devfn, int where, u32 * data)
{
	unsigned char busnum = bus->number;
	u32 intr;

	/* Clear status register bits. */
	MSC_WRITE(MSC01_PCI_INTSTAT,
		  (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT));

	MSC_WRITE(MSC01_PCI_CFGADDR,
		  ((busnum << MSC01_PCI_CFGADDR_BNUM_SHF) |
		   (PCI_SLOT(devfn) << MSC01_PCI_CFGADDR_DNUM_SHF) |
		   (PCI_FUNC(devfn) << MSC01_PCI_CFGADDR_FNUM_SHF) |
		   ((where / 4) << MSC01_PCI_CFGADDR_RNUM_SHF)));

	/* Perform access */
	if (access_type == PCI_ACCESS_WRITE)
		MSC_WRITE(MSC01_PCI_CFGDATA, *data);
	else
		MSC_READ(MSC01_PCI_CFGDATA, *data);

	/* Detect Master/Target abort */
	MSC_READ(MSC01_PCI_INTSTAT, intr);
	if (intr & (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT)) {
		/* Error occurred */

		/* Clear bits */
		MSC_WRITE(MSC01_PCI_INTSTAT,
			  (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT));

		return -1;
	}

	return 0;
}