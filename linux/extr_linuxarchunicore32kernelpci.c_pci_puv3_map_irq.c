#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */

__attribute__((used)) static int pci_puv3_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (dev->bus->number == 0) {
#ifdef CONFIG_ARCH_FPGA /* 4 pci slots */
		if      (dev->devfn == 0x00)
			return IRQ_PCIINTA;
		else if (dev->devfn == 0x08)
			return IRQ_PCIINTB;
		else if (dev->devfn == 0x10)
			return IRQ_PCIINTC;
		else if (dev->devfn == 0x18)
			return IRQ_PCIINTD;
#endif
#ifdef CONFIG_PUV3_DB0913 /* 3 pci slots */
		if      (dev->devfn == 0x30)
			return IRQ_PCIINTB;
		else if (dev->devfn == 0x60)
			return IRQ_PCIINTC;
		else if (dev->devfn == 0x58)
			return IRQ_PCIINTD;
#endif
#if	defined(CONFIG_PUV3_NB0916) || defined(CONFIG_PUV3_SMW0919)
		/* only support 2 pci devices */
		if      (dev->devfn == 0x00)
			return IRQ_PCIINTC; /* sata */
#endif
	}
	return -1;
}