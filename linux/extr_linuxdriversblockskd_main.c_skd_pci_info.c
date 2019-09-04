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
typedef  int uint16_t ;
struct skd_device {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  lwstr ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *skd_pci_info(struct skd_device *skdev, char *str)
{
	int pcie_reg;

	strcpy(str, "PCIe (");
	pcie_reg = pci_find_capability(skdev->pdev, PCI_CAP_ID_EXP);

	if (pcie_reg) {

		char lwstr[6];
		uint16_t pcie_lstat, lspeed, lwidth;

		pcie_reg += 0x12;
		pci_read_config_word(skdev->pdev, pcie_reg, &pcie_lstat);
		lspeed = pcie_lstat & (0xF);
		lwidth = (pcie_lstat & 0x3F0) >> 4;

		if (lspeed == 1)
			strcat(str, "2.5GT/s ");
		else if (lspeed == 2)
			strcat(str, "5.0GT/s ");
		else
			strcat(str, "<unknown> ");
		snprintf(lwstr, sizeof(lwstr), "%dX)", lwidth);
		strcat(str, lwstr);
	}
	return str;
}