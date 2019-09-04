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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
#define  ATA_100 134 
#define  ATA_100a 133 
#define  ATA_133 132 
#define  ATA_133a 131 
#define  ATA_16 130 
#define  ATA_33 129 
#define  ATA_66 128 
 int PCI_LATENCY_TIMER ; 
 int chipset_family ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 

__attribute__((used)) static int init_chipset_sis5513(struct pci_dev *dev)
{
	/* Make general config ops here
	   1/ tell IDE channels to operate in Compatibility mode only
	   2/ tell old chips to allow per drive IDE timings */

	u8 reg;
	u16 regw;

	switch (chipset_family) {
	case ATA_133:
		/* SiS962 operation mode */
		pci_read_config_word(dev, 0x50, &regw);
		if (regw & 0x08)
			pci_write_config_word(dev, 0x50, regw&0xfff7);
		pci_read_config_word(dev, 0x52, &regw);
		if (regw & 0x08)
			pci_write_config_word(dev, 0x52, regw&0xfff7);
		break;
	case ATA_133a:
	case ATA_100:
		/* Fixup latency */
		pci_write_config_byte(dev, PCI_LATENCY_TIMER, 0x80);
		/* Set compatibility bit */
		pci_read_config_byte(dev, 0x49, &reg);
		if (!(reg & 0x01))
			pci_write_config_byte(dev, 0x49, reg|0x01);
		break;
	case ATA_100a:
	case ATA_66:
		/* Fixup latency */
		pci_write_config_byte(dev, PCI_LATENCY_TIMER, 0x10);

		/* On ATA_66 chips the bit was elsewhere */
		pci_read_config_byte(dev, 0x52, &reg);
		if (!(reg & 0x04))
			pci_write_config_byte(dev, 0x52, reg|0x04);
		break;
	case ATA_33:
		/* On ATA_33 we didn't have a single bit to set */
		pci_read_config_byte(dev, 0x09, &reg);
		if ((reg & 0x0f) != 0x00)
			pci_write_config_byte(dev, 0x09, reg&0xf0);
		/* fall through */
	case ATA_16:
		/* force per drive recovery and active timings
		   needed on ATA_33 and below chips */
		pci_read_config_byte(dev, 0x52, &reg);
		if (!(reg & 0x08))
			pci_write_config_byte(dev, 0x52, reg|0x08);
		break;
	}

	return 0;
}