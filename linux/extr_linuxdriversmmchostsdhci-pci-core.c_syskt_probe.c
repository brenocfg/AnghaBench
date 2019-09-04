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
struct sdhci_pci_chip {TYPE_1__* pdev; } ;
struct TYPE_2__ {int class; } ;

/* Variables and functions */
 int PCI_SDHCI_IFDMA ; 
 int PCI_SDHCI_IFVENDOR ; 

__attribute__((used)) static int syskt_probe(struct sdhci_pci_chip *chip)
{
	if ((chip->pdev->class & 0x0000FF) == PCI_SDHCI_IFVENDOR) {
		chip->pdev->class &= ~0x0000FF;
		chip->pdev->class |= PCI_SDHCI_IFDMA;
	}
	return 0;
}