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
 int IORESOURCE_MEM ; 
 int PCI_ROM_RESOURCE ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 int pci_resource_len (struct pci_dev*,int) ; 

__attribute__((used)) static int jmb38x_ms_count_slots(struct pci_dev *pdev)
{
	int cnt, rc = 0;

	for (cnt = 0; cnt < PCI_ROM_RESOURCE; ++cnt) {
		if (!(IORESOURCE_MEM & pci_resource_flags(pdev, cnt)))
			break;

		if (256 != pci_resource_len(pdev, cnt))
			break;

		++rc;
	}
	return rc;
}