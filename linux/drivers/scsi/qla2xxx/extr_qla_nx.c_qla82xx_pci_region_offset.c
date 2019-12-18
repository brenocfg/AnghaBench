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
typedef  unsigned long u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned long QLA82XX_MSIX_TBL_SPACE ; 
 int /*<<< orphan*/  QLA82XX_PCI_REG_MSIX_TBL ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned long*) ; 

int qla82xx_pci_region_offset(struct pci_dev *pdev, int region)
{
	unsigned long val = 0;
	u32 control;

	switch (region) {
	case 0:
		val = 0;
		break;
	case 1:
		pci_read_config_dword(pdev, QLA82XX_PCI_REG_MSIX_TBL, &control);
		val = control + QLA82XX_MSIX_TBL_SPACE;
		break;
	}
	return val;
}