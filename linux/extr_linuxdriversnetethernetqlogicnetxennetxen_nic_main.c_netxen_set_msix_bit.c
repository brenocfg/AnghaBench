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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {scalar_t__ msix_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_MSIX_FLAGS_ENABLE ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netxen_set_msix_bit(struct pci_dev *pdev, int enable)
{
	u32 control;

	if (pdev->msix_cap) {
		pci_read_config_dword(pdev, pdev->msix_cap, &control);
		if (enable)
			control |= PCI_MSIX_FLAGS_ENABLE;
		else
			control = 0;
		pci_write_config_dword(pdev, pdev->msix_cap, control);
	}
}