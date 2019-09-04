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

__attribute__((used)) static int pdev_is_sata(struct pci_dev *pdev)
{
#ifdef CONFIG_BLK_DEV_IDE_SATA
	switch (pdev->device) {
	case PCI_DEVICE_ID_SII_3112:
	case PCI_DEVICE_ID_SII_1210SA:
		return 1;
	case PCI_DEVICE_ID_SII_680:
		return 0;
	}
	BUG();
#endif
	return 0;
}