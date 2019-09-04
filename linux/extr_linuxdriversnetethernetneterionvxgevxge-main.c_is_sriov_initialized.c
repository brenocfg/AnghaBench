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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 scalar_t__ PCI_SRIOV_CTRL ; 
 int PCI_SRIOV_CTRL_VFE ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static int is_sriov_initialized(struct pci_dev *pdev)
{
	int pos;
	u16 ctrl;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	if (pos) {
		pci_read_config_word(pdev, pos + PCI_SRIOV_CTRL, &ctrl);
		if (ctrl & PCI_SRIOV_CTRL_VFE)
			return 1;
	}
	return 0;
}