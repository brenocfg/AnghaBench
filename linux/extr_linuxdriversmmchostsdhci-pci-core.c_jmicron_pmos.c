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
struct sdhci_pci_chip {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int pci_read_config_byte (int /*<<< orphan*/ ,int,int*) ; 
 int pci_write_config_byte (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int jmicron_pmos(struct sdhci_pci_chip *chip, int on)
{
	u8 scratch;
	int ret;

	ret = pci_read_config_byte(chip->pdev, 0xAE, &scratch);
	if (ret)
		return ret;

	/*
	 * Turn PMOS on [bit 0], set over current detection to 2.4 V
	 * [bit 1:2] and enable over current debouncing [bit 6].
	 */
	if (on)
		scratch |= 0x47;
	else
		scratch &= ~0x47;

	return pci_write_config_byte(chip->pdev, 0xAE, scratch);
}