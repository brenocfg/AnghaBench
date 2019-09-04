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
struct sdhci_pci_chip {int num_slots; } ;

/* Variables and functions */

__attribute__((used)) static int mrst_hc_probe(struct sdhci_pci_chip *chip)
{
	/*
	 * slots number is fixed here for MRST as SDIO3/5 are never used and
	 * have hardware bugs.
	 */
	chip->num_slots = 1;
	return 0;
}