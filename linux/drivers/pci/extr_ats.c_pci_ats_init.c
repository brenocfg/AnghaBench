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
struct pci_dev {int ats_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ATS ; 
 scalar_t__ pci_ats_disabled () ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 

void pci_ats_init(struct pci_dev *dev)
{
	int pos;

	if (pci_ats_disabled())
		return;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ATS);
	if (!pos)
		return;

	dev->ats_cap = pos;
}