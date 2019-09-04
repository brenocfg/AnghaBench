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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_ERR_UNCOR_SEVER ; 
 int /*<<< orphan*/  PCI_ERR_UNC_COMP_ABORT ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_disable_aer_comp_abort(struct pci_dev *pdev)
{
	u32 err_sev;
	int pos;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ERR);
	if (!pos)
		return;

	pci_read_config_dword(pdev, pos + PCI_ERR_UNCOR_SEVER, &err_sev);
	err_sev &= ~PCI_ERR_UNC_COMP_ABORT;
	pci_write_config_dword(pdev, pos + PCI_ERR_UNCOR_SEVER, err_sev);
}