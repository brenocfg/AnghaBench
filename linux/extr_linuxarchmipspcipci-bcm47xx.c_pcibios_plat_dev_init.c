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

int pcibios_plat_dev_init(struct pci_dev *dev)
{
#ifdef CONFIG_BCM47XX_SSB
	if (bcm47xx_bus_type ==	 BCM47XX_BUS_TYPE_SSB)
		return bcm47xx_pcibios_plat_dev_init_ssb(dev);
	else
#endif
#ifdef CONFIG_BCM47XX_BCMA
	if  (bcm47xx_bus_type ==  BCM47XX_BUS_TYPE_BCMA)
		return bcm47xx_pcibios_plat_dev_init_bcma(dev);
	else
#endif
		return 0;
}