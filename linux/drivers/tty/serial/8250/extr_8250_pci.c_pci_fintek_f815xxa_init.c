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
struct pci_dev {int device; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int IORESOURCE_MEM ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static int pci_fintek_f815xxa_init(struct pci_dev *dev)
{
	u32 max_port, i;
	int config_base;

	if (!(pci_resource_flags(dev, 0) & IORESOURCE_MEM))
		return -ENODEV;

	switch (dev->device) {
	case 0x1204: /* 4 ports */
	case 0x1208: /* 8 ports */
		max_port = dev->device & 0xff;
		break;
	case 0x1212: /* 12 ports */
		max_port = 12;
		break;
	default:
		return -EINVAL;
	}

	/* Set to mmio decode */
	pci_write_config_byte(dev, 0x209, 0x40);

	for (i = 0; i < max_port; ++i) {
		/* UART0 configuration offset start from 0x2A0 */
		config_base = 0x2A0 + 0x08 * i;

		/* Select 128-byte FIFO and 8x FIFO threshold */
		pci_write_config_byte(dev, config_base + 0x01, 0x33);

		/* Enable UART I/O port */
		pci_write_config_byte(dev, config_base + 0, 0x01);
	}

	return max_port;
}