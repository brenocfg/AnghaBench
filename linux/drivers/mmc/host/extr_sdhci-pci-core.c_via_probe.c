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
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_QUIRK_DELAY_AFTER_POWER ; 

__attribute__((used)) static int via_probe(struct sdhci_pci_chip *chip)
{
	if (chip->pdev->revision == 0x10)
		chip->quirks |= SDHCI_QUIRK_DELAY_AFTER_POWER;

	return 0;
}