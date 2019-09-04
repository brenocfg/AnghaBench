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
struct sdhci_pci_chip {int /*<<< orphan*/  quirks; TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ subsystem_vendor; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_SAMSUNG ; 
 scalar_t__ PCI_VENDOR_ID_SONY ; 
 int /*<<< orphan*/  SDHCI_QUIRK_NO_CARD_NO_RESET ; 

__attribute__((used)) static int ricoh_probe(struct sdhci_pci_chip *chip)
{
	if (chip->pdev->subsystem_vendor == PCI_VENDOR_ID_SAMSUNG ||
	    chip->pdev->subsystem_vendor == PCI_VENDOR_ID_SONY)
		chip->quirks |= SDHCI_QUIRK_NO_CARD_NO_RESET;
	return 0;
}