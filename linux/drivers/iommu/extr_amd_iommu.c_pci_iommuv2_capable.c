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
#define  PCI_EXT_CAP_ID_ATS 130 
#define  PCI_EXT_CAP_ID_PASID 129 
#define  PCI_EXT_CAP_ID_PRI 128 
 scalar_t__ pci_ats_disabled () ; 
 int pci_find_ext_capability (struct pci_dev*,int const) ; 

__attribute__((used)) static bool pci_iommuv2_capable(struct pci_dev *pdev)
{
	static const int caps[] = {
		PCI_EXT_CAP_ID_ATS,
		PCI_EXT_CAP_ID_PRI,
		PCI_EXT_CAP_ID_PASID,
	};
	int i, pos;

	if (pci_ats_disabled())
		return false;

	for (i = 0; i < 3; ++i) {
		pos = pci_find_ext_capability(pdev, caps[i]);
		if (pos == 0)
			return false;
	}

	return true;
}