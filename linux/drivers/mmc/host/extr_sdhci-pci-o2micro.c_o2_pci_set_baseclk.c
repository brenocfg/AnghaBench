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
struct sdhci_pci_chip {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  O2_SD_PLL_SETTING ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void o2_pci_set_baseclk(struct sdhci_pci_chip *chip, u32 value)
{
	u32 scratch_32;

	pci_read_config_dword(chip->pdev,
			      O2_SD_PLL_SETTING, &scratch_32);

	scratch_32 &= 0x0000FFFF;
	scratch_32 |= value;

	pci_write_config_dword(chip->pdev,
			       O2_SD_PLL_SETTING, scratch_32);
}